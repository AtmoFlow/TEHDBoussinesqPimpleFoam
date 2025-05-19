{
alphat = turbulence->nut()/Prt;
alphat.correctBoundaryConditions();

volScalarField alphaEff("alphaEff", turbulence->nu()/Pr + alphat);
	fvScalarMatrix TEqn
		(
		 fvm::ddt(T)
		 + fvm::div(phi, T)
		 - fvm::laplacian(dimensionedScalar("TempConst",dimensionSet(0, 2, -1, 0, 0, 0,0),scalar(1)),T)
		 ==
		 fvOptions(T)
		);
	TEqn.relax();
	fvOptions.constrain(TEqn);
	TEqn.solve();

fvOptions.correct(T);

}
