//
// Created by diego on 3/31/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include <vector>

using namespace std;

int main() {

// THIS VERSION MUST BE CONSERVED WITHOUT MODIFICATION

    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    double energy(2);
    double quadrupoleIntensity(1.2);
    double sextupoleIntensity(1);
    double curvatureDipole(1);
    TextSupport s(cout);
    Accelerator bobLEponge(Vector3D(3, 0, 0));
    double radius(0.1);
    Vector3D endQuad1(3, 1.5, 0);
    Vector3D endSex1(3, 1, 0);
    Vector3D endSeg1(3, 0, 0);
    Vector3D endQuad2(3, -0.5, 0);
    Vector3D endSex2(3, -1, 0);
    Vector3D endSeg2(3, -2, 0);
    Vector3D endDip(2, -3, 0);

    for (int i = 0; i < 4; ++i) {
        bobLEponge.addQuadrupole(endQuad1, radius, -quadrupoleIntensity);
        bobLEponge.addSextupole(endSex1, radius, sextupoleIntensity);
        bobLEponge.addSegment(endSeg1, radius);
        bobLEponge.addQuadrupole(endQuad2, radius, quadrupoleIntensity);
        bobLEponge.addSextupole(endSex2, radius, sextupoleIntensity);
        bobLEponge.addSegment(endSeg2, radius);
        bobLEponge.addDipole(endDip, radius, curvatureDipole, mass, charge, energy);

        endQuad1 = endQuad1 ^ Vector3D::e3;
        endSex1 = endSex1 ^ Vector3D::e3;
        endSeg1 = endSeg1 ^ Vector3D::e3;
        endQuad2 = endQuad2 ^ Vector3D::e3;
        endSex2 = endSex2 ^ Vector3D::e3;
        endSeg2 = endSeg2 ^ Vector3D::e3;
        endDip = endDip ^ Vector3D::e3;
    }

    // ---- Parametrisation of the particles ----
    Vector3D position2(2.99, 2, 0);
    Particle p2(mass, -charge, 2, position2, Vector3D(0, 1, 0), bobLEponge.elements()[18].get(), Vector3D());
    Particle p0(mass, charge, 2, Vector3D(2.99, 0, 0), Vector3D(0, -1, 0), bobLEponge.elements()[0].get());
    Particle dipHole(constants::M_PROTON, constants::C_PROTON, 2, Vector3D(3.01318, -2.01213, 0),
            Vector3D(-139591, -2.64754e+08, 0), bobLEponge.elements()[2].get());
//    vector<Particle> particles{dipHole};
    //  ---------

    bobLEponge.addParticle(p2);

    bobLEponge.draw(s);
//    int i(0);
//    while (!bobLEponge.particles().empty()) {
//        bobLEponge.evolve(1e-11);
//        ++i;
//    }
//    cout <<i<< endl;
    int i = 0;
    while (!bobLEponge.particles().empty()) {
        bobLEponge.evolve(1e-11);
        ++i;
        if (i % 1000000 == 1
        ) cout << i << endl;
    }
//    for (int j = 0; j < 10000000; ++j) {
//        bobLEponge.evolve(1e-12);
//        if (bobLEponge.particles().front()->element() == bobLEponge.elements()[2].get())
//            bobLEponge.draw(s);
//    }
    return 0;
}
