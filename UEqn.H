// Solve the momentum equation

MRF.correctBoundaryVelocity(U);

	fvVectorMatrix UEqn
	(
	 fvm::ddt(U) + fvm::div(phi, U)
	 + MRF.DDt(U)
	 + turbulence->divDevReff(U)
	 ==
	 fDEP
	 + fvOptions(U)
	);

	UEqn.relax();

	fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
	solve
		(
		 UEqn
		 ==
		 fvc::reconstruct
		 (
		  (
		   - fvc::snGrad(p_rgh)
		  )*mesh.magSf()
		 )
		);

	fvOptions.correct(U);
}

