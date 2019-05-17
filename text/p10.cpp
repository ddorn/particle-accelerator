//
// Created by diego on 3/31/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include <vector>

using namespace std;

int main() {


    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    double energy(2);
    double quadrupoleIntensity(1.2);
//    double dipoleIntensity(5.89158);
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
        bobLEponge.addDipole(pd, radius, 1, mass, charge, energy);
        bobLEponge.addQuadrupole(pqd, radius, quadrupoleIntensity);
        bobLEponge.addSegment(pd2, radius);

        pqf = pqf ^ Vector3D::e3;
        pd1 = pd1 ^ Vector3D::e3;
        pd = pd ^ Vector3D::e3;
        pqd = pqd ^ Vector3D::e3;
        pd2 = pd2 ^ Vector3D::e3;
    }

    // ---- Parametrisation of the particles ----
    Vector3D position2(2.99, 2, 0);
    Particle p2(mass, -charge, 2, position2, Vector3D(0, 1, 0), bobLEponge.elements()[18].get(), Vector3D());
    Particle p0(mass, charge, 2, Vector3D(2.99, 0, 0), Vector3D(0, -1, 0), bobLEponge.elements()[0].get());
    Particle dipHole(constants::M_PROTON, constants::C_PROTON, 2, Vector3D(3.01318, -2.01213, 0),
            Vector3D(-139591, -2.64754e+08, 0), bobLEponge.elements()[2].get());
//    vector<Particle> particles{dipHole};
    //  ---------

//    bobLEponge.addParticle(make_shared<Particle>(p2));
    bobLEponge.cleanParticles();
    bobLEponge.addCircularBeam(mass, charge, 2, -Vector3D::e2, 1, 1, Vector3D(), 0);
//    int i(0);
//    while (!bobLEponge.particles()->empty()) {
//        bobLEponge.evolve(1e-11);
//        bobLEponge.draw(s);
//        ++i;
//    }
//    cout <<i<< endl;

//    int i = 0;
//    while (!bobLEponge.particles()->isHead()) {
//        bobLEponge.evolve(1e-11);
//        ++i;
//        if (i % 1000000 == 1
//        ) cout << i << endl;
//    }

    for (int j = 0; j < 10000; ++j) {
        bobLEponge.evolve(1e-11);
//        if (bobLEponge.particles().front()->element() == bobLEponge.elements()[2].get())
    }
    bobLEponge.draw(s);
    return 0;
}
