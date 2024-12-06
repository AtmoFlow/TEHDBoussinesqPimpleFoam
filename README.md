![example workflow](https://github.com/AtmoFlow/TEHDBoussinesqPimpleFoam/actions/workflows/build-OF.yml/badge.svg)

# Introduction

TEHDBoussinesqPimpleFoam is a solver developed for OpenFOAM, a powerful open-source computational fluid dynamics (CFD) software. This solver is designed to handle thermo-electro-hydrodynamic (TEHD) problems, providing a comprehensive toolset for simulating complex interactions between thermal, electrical, and fluidic phenomena.
Features in incompressible flows. It also can solve problems in a non-dimensional way.

# Running the solver
## Installation
Clone this repository:

`git clone git@github.com:AtmoFlow/TEHDBoussinesqPimpleFoam.git`

Compile the solver. This requires the OpenFoam development tools (base-dev or devel)

`wmake` 

## Configuration
Consistent with the scientific community around TEHD, the solver can solve directly in a non-dimensional way. A detailed description of the scaling of variables to obtain a dimensionless equation is provided in the paper. Turbulent flow can only be solved with the dimension-affected solver. By default, the solver runs dimensional. To enable dimensionless calculation add `solveDimless yes;` to the  `transportProperties` file. For scaling purposes, the non-dimensional solver requires additional properties such as the heat diffusion `kappa` and the geometric length scale `d` defined in the same file.

**Additional TEHD settings**
The solver is derived from the `buoyantBoussinesqPimpleFoam`. In addition to solving TEHD, the electric potential needs to be defined as `Ue` in Volts for the boundaries. `zeroGradient` needs to be set to electric inert boundaries. Additionally, further transport properties need to be defined to solve the dielectrophoretic force, such as the relative permittivity reference `epsilonr0` value at temperature `TRef` but its expansion coefficient `e` analogous to the Boussinesq approximation for buoyant flows.
Moreover, the solver can process dielectric heating for polar fluids under the influence of an alternative current. For this, the `dielectricHeat yes;` setting needs to be added to the `transportProperties`. Then, the solver requires further properties: the frequency `f` of the alternative source, the heat capacity `Cp`, and the dissipation factor `hdiss`.

**Rotating reference frame**
The solver can solve rotating problems in a rotating reference frame, defining the apparent forces, Coriolis force, and centrifugal force. The rotation axis is not adjustable and is defined as the origin z-axis. The solver considers centrifugal buoyancy by setting the density expansion coefficient `beta`. The rotation rate is defined as scalar `omega` in the transport properties.

## Tutorials
The *example* folder provides two examples for the same parameter setting, with the case in the *non-dim* folder running dimensionless and the case in the *dim* running dimensional. `Allrun` runs the mesh construction and decomposition on two cores and starts the parallel calculation, while `Allclean` returns to the initial state. Two different `0` folders are located in these folders. First, the `0.isotherm` defines uniform temperature boundary conditions while `0.atmospheric` mimics an atmospheric-like temperature boundary condition used in the paper. The uniform boundary condition is chosen for the tutorial to save calculation resources since the convection develops faster.

## Contribution
Contributions are welcome! If you find any issues or have ideas for improvements, please open an issue or submit a pull request.
License

## Acknowledgments

This work is supported by the Bundesministerium für Wirtschaft und Klimaschutz (BMWK) via the German Space Administration (DLR) with grant no. 50WM1841, 50WM2141 and 50WM2441. The numerical
calculations for the development were conducted with computing resources of the National High Performance (NHR) Computing infrastructure that received the funding to the project number bbi00021.

Happy simulating!
