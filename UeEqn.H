{

// Info<< "calculate Laplacian Ue\n" << endl;
if(!bSolveDimless)
{
	fvScalarMatrix UeEqn
		(
		 - fvm::laplacian(epsilonr, Ue)
		);
	UeEqn.relax();
	fvOptions.constrain(UeEqn);
	UeEqn.solve();
	fvOptions.correct(Ue);

}
else
{
	fvScalarMatrix UeEqn
		(
		 - fvm::laplacian(fUe1scaling, Ue)+ fvm::laplacian(fUe2scaling*T, Ue)
		);
	UeEqn.relax();
	fvOptions.constrain(UeEqn);
	UeEqn.solve();
	fvOptions.correct(Ue);
}

if(!bSolveDimless)
{
	fDEP	=	- 0.5
		* Foam::constant::electromagnetic::epsilon0 
		* magSqr(fvc::grad(Ue))     
		* Foam::fvc::grad(epsilonr)/rho0;
}else{
	fDEP    =        fDEPscaling
		* magSqr(fvc::grad(Ue))
		* Foam::fvc::grad(T);
}



}
