singlePhaseTransportModel laminarTransport(U, phi);


// Thermo-electro parameter
dimensionedScalar gamma_e("gamma_e",dimensionSet(0, 0, 0, -1, 0, 0,0),laminarTransport);

//Rayleigh number
dimensionedScalar RaE("RaE",dimensionSet(-2, 0, 4, -1, 0, 2,0),laminarTransport);

// Laminar Prandtl number
dimensionedScalar Pr("Pr", dimless, laminarTransport);

// Turbulent Prandtl number
dimensionedScalar Prt("Prt", dimless, laminarTransport);


Info<<"Ra_E="<< RaE <<nl;
Info<<"gamma_e"<< gamma_e <<nl;
Info<<"Pr"<< Pr <<nl;


