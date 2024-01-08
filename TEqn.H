{
alphat = turbulence->nut()/Prt;
alphat.correctBoundaryConditions();

volScalarField alphaEff("alphaEff", turbulence->nu()/Pr + alphat);
if(!bSolveDimless)
{
	fvScalarMatrix TEqn
		(
		 fvm::ddt(T)
		 + fvm::div(phi, T)
		 - fvm::laplacian(alphaEff, T)
		 ==
		 dielectricHeatConst*magSqr(fvc::grad(Ue))
		 + radiation->ST(rhoCpRef, T)
		 + fvOptions(T)
		);
	TEqn.relax();
	fvOptions.constrain(TEqn);
	TEqn.solve();
	radiation->correct();
}else{
	fvScalarMatrix TEqn
		(
		 fvm::ddt(T)
		 + fvm::div(phi, T)
		 - fvm::laplacian(dimensionedScalar("TempConst",dimensionSet(0, 2, -1, 0, 0, 0,0),scalar(1)),T)
		 ==
		 dielHeatScaling*dielectricHeatConst*magSqr(fvc::grad(Ue))
		 + fvOptions(T)
		);
	TEqn.relax();
	fvOptions.constrain(TEqn);
	TEqn.solve();
}

fvOptions.correct(T);

rhok = 1.0 - beta*(T - TRef);

rho= rho0*(1.0 - beta*(T - TRef));

epsilonr=epsilonr0*(1.0 - e*(T - TRef));

}
