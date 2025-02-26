singlePhaseTransportModel laminarTransport(U, phi);


dimensionedScalar rho0("rho0", dimDensity, laminarTransport);
// Thermal expansion coefficient [1/K]
dimensionedScalar beta("beta",dimless/dimTemperature,laminarTransport);

dimensionedScalar epsilonr0("epsilonr0", dimless, laminarTransport);
// Thermal permetivity expansion coefficient [1/K]
dimensionedScalar e("e",dimless/dimTemperature,laminarTransport);

// Reference temperature [K]
dimensionedScalar TRef("TRef", dimTemperature, laminarTransport);

// Laminar Prandtl number
dimensionedScalar Pr("Pr", dimless, laminarTransport);

// Turbulent Prandtl number
dimensionedScalar Prt("Prt", dimless, laminarTransport);

dimensionedScalar omega(dimensionedScalar::getOrDefault("omega", laminarTransport, dimensionSet(0, 0, -1, 0, 0, 0, 0), 0));

//Set the scaling for dimless calculation
dimensionedScalar fDEPscaling("fDEPscaling",  dimensionSet(-2, 0, 4, -1, 0, 2,0), 0);

dimensionedScalar fC1scaling("fC1scaling", dimensionSet(0, 0, 0, 0, 0, 0,0), 0);
dimensionedScalar fC2scaling("fC2scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), 0);
dimensionedScalar fC3scaling("fC3scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), 0);

dimensionedScalar fCorio1scaling("fCorio1scaling", dimensionSet(0, 0, 0, 0, 0, 0,0), 0);
dimensionedScalar fCorio2scaling("fCorio2scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), 0);

dimensionedScalar fUe1scaling("fUe1scaling", dimensionSet(0, 0, 0, 0, 0, 0,0), 0);
dimensionedScalar fUe2scaling("fUe2scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), 0);

dimensionedScalar dielectricHeatConst("dielectricHeatConst", dimensionSet(-2, -2, 5, 1, 0, 2,0), 0);

bool bDielHeat = laminarTransport.getOrDefault<bool>("dielectricHeat", false);

dimensionedScalar dielHeatScaling("dielHeatScaling",dimless,0);

if(bDielHeat){
Info<<"Added dielectric heating  \n"<<nl;
dimensionedScalar hdiss("hdiss", dimensionSet(0, 0, 0, 0, 0, 0, 0), laminarTransport);
dimensionedScalar Cp("Cp", dimensionSet(0, 2, -2, -1, 0, 0, 0), laminarTransport);
dimensionedScalar f("f", dimensionSet(0, 0, -1, 0, 0, 0, 0), laminarTransport);

dielectricHeatConst=2*Foam::constant::mathematical::pi*f*Foam::constant::electromagnetic::epsilon0*epsilonr0*hdiss/(Cp*rho0);

}

bool bSolveDimless = laminarTransport.getOrDefault<bool>("solveDimless", false);

if(bSolveDimless)
{
dimensionedScalar kappa("kappa", dimensionSet(0, 2, -1, 0, 0, 0,0), laminarTransport);

//Get boundary condition for dimless calculation
dimensionedScalar DeltaT("DeltaT", dimensionSet(0, 0, 0, 1, 0, 0,0), laminarTransport);
dimensionedScalar Vrms("Vrms", dimensionSet(1, 2, -3, 0, 0, -1,0), laminarTransport);
dimensionedScalar d("d", dimensionSet(0, 1, 0, 0, 0, 0,0), laminarTransport);

//Set the scaling for dimless calculation
fDEPscaling=dimensionedScalar("fDEPscaling",  dimensionSet(-2, 0, 4, -1, 0, 2,0), Foam::constant::electromagnetic::epsilon0.value()*epsilonr0.value()*e.value()*DeltaT.value()*pow(Vrms.value(),2)/(2*pow(kappa.value(),2)*rho0.value()));

fC1scaling=dimensionedScalar("fC1scaling", dimensionSet(0, 0, 0, 0, 0, 0,0), pow(omega.value(),2)*pow(d.value(),4)/pow(kappa.value(),2));
fC2scaling=dimensionedScalar("fC2scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), pow(omega.value(),2)*pow(d.value(),4)*beta.value()*DeltaT.value()/pow(kappa.value(),2));
fC3scaling=dimensionedScalar("fC3scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), beta.value()*DeltaT.value());

fCorio1scaling=dimensionedScalar("fCorio1scaling", dimensionSet(0, 0, 0, 0, 0, 0,0), omega.value()*pow(d.value(),2)/kappa.value());
fCorio2scaling=dimensionedScalar("fCorio2scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), omega.value()*pow(d.value(),2)*beta.value()*DeltaT.value()/kappa.value());

fUe1scaling=dimensionedScalar("fUe1scaling", dimensionSet(0, 0, 0, 0, 0, 0,0), 1);
fUe2scaling=dimensionedScalar("fUe2scaling", dimensionSet(0, 0, 0, -1, 0, 0,0), e.value()*DeltaT.value());

dielHeatScaling=dimensionedScalar("dielHeatScaling",dimless,pow(Vrms.value(),2)/(kappa.value()*DeltaT.value()));

Info<<"Calculate dimensionless read scaling quantities. Note all other quantities need to be 1"<<nl;
if(omega.value()!=0){
omega=dimensionedScalar("omega", dimensionSet(0, 0, -1, 0, 0, 0,0) , 1);
}

//Set all dimension affected values to 1

rho0=dimensionedScalar("rho0", dimDensity, 1);
beta=dimensionedScalar("beta",dimless/dimTemperature,1);

epsilonr0=dimensionedScalar("epsilonr0", dimless, 1);
e=dimensionedScalar(    "e",    dimless/dimTemperature,   1);


TRef=dimensionedScalar("TRef", dimTemperature, 0);



}else{
Info<<"Calculate dimension quantities"<<nl;
}
dimensionedVector Romega("Romega", dimensionSet(0, 0, -1, 0, 0, 0,0) , vector(0,0,omega.value()));

Info<< laminarTransport.nu()  <<nl;
Info<< rho0 <<nl;
Info<< beta <<nl;
Info<< epsilonr0 <<nl;
Info<< e <<nl;
Info<< TRef <<nl;
Info<< Pr <<nl;
Info<< Prt <<nl;
Info<< Romega <<nl;
Info<< fDEPscaling <<nl;
Info<< fC1scaling <<nl;
Info<< fC2scaling <<nl;
Info<< fCorio1scaling <<nl;
Info<< fCorio2scaling<<nl;
Info<< fUe1scaling <<nl;
Info<< fUe2scaling <<nl;
Info<< dielHeatScaling<<nl;
Info<< dielectricHeatConst<<nl<<nl;

Info<<"Ra_E="<< fDEPscaling.value()/Pr.value() <<nl;
Info<<"Ta="<< fC1scaling.value()*4*pow(Pr.value(),-2) <<nl;
if (dielHeatScaling.value()*dielectricHeatConst.value()>0){
Info<<"Ra_T="<< fDEPscaling.value()/Pr.value()/(dielHeatScaling.value()*dielectricHeatConst.value()) <<nl;
}
