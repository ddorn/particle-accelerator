//
// Created by diego on 3/31/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include <vector>

using namespace std;

int main() {


    double quadrupoleIntensity(1.2);
    double dipoleIntensity(5.89158);
    TextSupport s(cout);
    Accelerator bobLEponge(Vector3D(3, 0, 0));

    double radius(0.1);
    Vector3D pqf(3, -1, 0);
    Vector3D pd1(3, -2, 0);
    Vector3D pd(2, -3, 0);
    Vector3D pqd(1, -3, 0);
    Vector3D pd2(0, -3, 0);

    for (int i = 0; i < 4; ++i) {
        bobLEponge.addQuadrupole(pqf, radius, -quadrupoleIntensity);
        bobLEponge.addSegment(pd1, radius);
        bobLEponge.addDipole(pd, radius, 1, dipoleIntensity);
        bobLEponge.addQuadrupole(pqd, radius, quadrupoleIntensity);
        bobLEponge.addSegment(pd2, radius);

        pqf = pqf ^ Vector3D::e3;
        pd1 = pd1 ^ Vector3D::e3;
        pd = pd ^ Vector3D::e3;
        pqd = pqd ^ Vector3D::e3;
        pd2 = pd2 ^ Vector3D::e3;
    }

    // ---- Parametrisation of the particles ----
    Vector3D speed(0, -2.64754e08, 0); // constants::LIGHT_SPEED_MS);
    double gamma(2.13158);
    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    Vector3D momentum(speed * gamma * mass / constants::KG);
    Vector3D position1(3.01, 0, 0);
    Vector3D position2(2.99, 0, 0);
    Particle p2(mass, charge, 2, position2, momentum, Vector3D(), bobLEponge.elements()[0].get());
    vector<Particle> particles{p2};
    //  ---------
    bobLEponge.addParticle(p2);

    bobLEponge.draw(s);
//    int i(0);
//    while (!bobLEponge.particles().empty()) {
//        bobLEponge.evolve(1e-11);
//        ++i;
//    }
//    cout <<i<< endl;
    for (int j = 0; j < 2200; ++j) {
        bobLEponge.evolve();
        bobLEponge.draw(s);
    }
    return 0;
}