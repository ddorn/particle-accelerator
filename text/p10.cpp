//
// Created by diego on 3/31/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include <vector>

using namespace std;

int main() {
    // Parameters of particles
    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    double energy(2);
    Vector3D position1(2.99, 0, 0);
    Vector3D position2(3.01, 0, 0);

    // Creation of the accelerator
    TextSupport s(cout);
    Accelerator bobLEponge(Vector3D(3, 2, 0));


    double radius(0.1);

    Vector3D pDipole(2, -3, 0);
    Vector3D pFodo(3, -2, 0);

    for (int i = 0; i < 4; ++i) {
        bobLEponge.addFODO(pFodo, 1, radius, 1.2);
        bobLEponge.addDipole(pDipole, radius, 1, mass, charge, energy);

        pDipole = pDipole ^ Vector3D::e3;
        pFodo = pFodo ^ Vector3D::e3;
    }

    bobLEponge.addParticle(mass, charge, energy, position1, -Vector3D::e2);
    bobLEponge.addParticle(mass, charge, energy, position2, -Vector3D::e2);

    bobLEponge.showElements(cout);

    int i(0);
    while (!bobLEponge.particles()->empty()) {
        bobLEponge.evolve(1e-11);
        bobLEponge.draw(s);
        ++i;
    }

    return 0;
}
