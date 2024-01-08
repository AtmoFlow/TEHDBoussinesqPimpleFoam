// Solve the momentum equation

MRF.correctBoundaryVelocity(U);

	fvVectorMatrix UEqn
	(
	 fvm::ddt(U) + fvm::div(phi, U)
	 + MRF.DDt(U)
	 + turbulence->divDevReff(U)
	 ==
	 fDEP
	 - fC
	 - fCorio
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
		   - ghf*fvc::snGrad(rhok)
		   - fvc::snGrad(p_rgh)
		  )*mesh.magSf()
		 )
		);

	fvOptions.correct(U);
}


if(!bSolveDimless)
{
	fC = (Romega ^ ((Romega) ^ (mesh.C() ))) - beta*(T-TRef)*(
			(Romega ^ ((Romega) ^ (mesh.C() )))+
			((U^mesh.C())^((U^mesh.C())^mesh.C()))/(magSqr(magSqr(mesh.C())))
			);
	fCorio = 2.0 * (Romega ^ U) ;
}else{
	fC = 
		fC1scaling*(Romega ^ ((Romega) ^ (mesh.C() )))-T*(
				fC2scaling*(Romega ^ ((Romega) ^ (mesh.C()))) +
				fC3scaling*((U^mesh.C())^((U^mesh.C())^mesh.C()))/(magSqr(magSqr(mesh.C())))
				);
	fCorio = fCorio1scaling*2.0 * (Romega ^ U) ;
}
