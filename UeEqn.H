{

// Info<< "calculate Laplacian Ue\n" << endl;
	fvScalarMatrix UeEqn
		(
		 - fvm::laplacian(dimensionedScalar("one", dimensionSet(0, 0, 0, 0, 0, 0,0), 1), Ue)+ fvm::laplacian(gamma_e*T, Ue)
		);
	UeEqn.relax();
	fvOptions.constrain(UeEqn);
	UeEqn.solve();
	fvOptions.correct(Ue);

	fDEP    = Pr*RaE
		* magSqr(fvc::grad(Ue))
		* Foam::fvc::grad(T);

}
