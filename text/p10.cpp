//
// Created by diego on 3/31/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include <vector>

using namespace std;

int main() {
    // ---- Parametrisation of the particles ----
    Vector3D speed(Vector3D(0, -2.64754e08, 0) / constants::LIGHT_SPEED_MS);
    double gamma(2.13158);
    double mass(constants::M_PROTON);
    double charge(constants::PROTON_CHARGE);
    Vector3D momentum(speed * gamma * mass);
    Vector3D position1(3.01, 0, 0);
    Vector3D position2(2.99, 0, 0);
    Particle p1(mass, charge, position1, momentum);
    Particle p2(mass, charge, position2, momentum);
    vector<Particle> particles{p1, p2};
          //  ---------


    TextSupport s(cout);
    Accelerator bobLEponge(Vector3D(3, 0, 0));

    double radius(0.1);
    Vector3D pqf(3, -1, 0);
    Vector3D pd1(3, -2, 0);
    Vector3D pd(2, -3, 0);
    Vector3D pqd(1, -3, 0);
    Vector3D pd2(0, -3, 0);

    for (int i = 0; i < 4; ++i) {
        bobLEponge.addQuadrupole(pqf, radius, -1.2);
        bobLEponge.addSegment(pd1, radius);
        bobLEponge.addDipole(pd, radius, 1, 5.89158);
        bobLEponge.addQuadrupole(pqd, radius, 1.2);
        bobLEponge.addSegment(pd2, radius);

        pqf = pqf ^ Vector3D::e3;
        pd1 = pd1 ^ Vector3D::e3;
        pd = pd ^ Vector3D::e3;
        pqd = pqd ^ Vector3D::e3;
        pd2 = pd2 ^ Vector3D::e3;
    }

    bobLEponge.addBeam(mass, charge,
            momentum, 1, particles);

    bobLEponge.draw(s);
    /*
    for (int j = 0; j < 10; ++j) {
        bobLEponge.evolve();
        bobLEponge.draw(s);
    } */
    return 0;
}