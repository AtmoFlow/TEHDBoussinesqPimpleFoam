Info<< "Reading thermophysical properties\n" << endl;

Info<< "Reading field T\n" << endl;
volScalarField T
(
    IOobject
    (
        "T",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field p_rgh\n" << endl;
volScalarField p_rgh
(
    IOobject
    (
        "p_rgh",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

#include "readTransportProperties.H"

Info<< "Creating turbulence model\n" << endl;
autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

// Kinematic density for buoyancy force
volScalarField rhok
(
    IOobject
    (
        "rhok",
        runTime.timeName(),
        mesh
    ),
    1.0 - beta*(T - TRef)
);

// Kinematic density for buoyancy force
volScalarField rho
(       
        IOobject
                (
                "rho",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
        IOobject::AUTO_WRITE
        ),
    rho0*(1.0 - beta*(T - TRef))
);

Info<<"fC" << endl;
volVectorField fC
(        
         IOobject
          ( 
            "fC",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
            ),
            mesh,
        dimensionedVector("fC",dimensionSet(0, 1, -2, 0, 0, 0, 0),vector(0, 0, 0))
);

Info<<"fCorio" << endl;
volVectorField fCorio
(
         IOobject
          (
            "fCorio",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
            ),
            mesh,
        dimensionedVector("fCorio",dimensionSet(0, 1, -2, 0, 0, 0, 0),vector(0, 0, 0))
);


// kinematic turbulent thermal thermal conductivity m2/s
Info<< "Reading field alphat\n" << endl;
volScalarField alphat
(
    IOobject
    (
        "alphat",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

////////////Electric Properties ///////////////////////////////
Info<< "Reading field Electric Potential Ue\n" << endl;
volScalarField Ue
(   
    IOobject
    (   
        "Ue",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Ue",dimensionSet(1, 2, -3, 0, 0, -1,0), 0.0)
);

Info<< "Reading field epsilonr\n" << endl;
volScalarField epsilonr
(       
        IOobject
                (
                "epsilonr",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
        IOobject::AUTO_WRITE
        ),
        //mesh,
    //dimensionedScalar("epsilonr",dimensionSet(0, 0, 0, 0, 0, 0,0), 0.0)
	    epsilonr0*(1.0 - e*(T - TRef))
);

Info<<"fDEP" << endl;
volVectorField fDEP
(
         IOobject
          (
            "fDEP",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
            ),
            mesh,
        dimensionedVector("fDEP",dimensionSet(0, 1, -2, 0, 0, 0, 0),vector(0, 0, 0))
);


#include "readGravitationalAcceleration.H"
#include "readhRef.H"
#include "gh.H"


volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    p_rgh + rhok*gh
);

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell
(
    p,
    p_rgh,
    pimple.dict(),
    pRefCell,
    pRefValue
);

if (p_rgh.needReference())
{
    p += dimensionedScalar
    (
        "p",
        p.dimensions(),
        pRefValue - getRefCellValue(p, pRefCell)
    );
}

mesh.setFluxRequired(p_rgh.name());

#include "createMRF.H"
#include "createIncompressibleRadiationModel.H"
#include "createFvOptions.H"
