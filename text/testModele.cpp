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

// --- PARAMETRISATION OF PARTICLES ---
    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    double energy(2);
// ------------------------------------

// --- PARAMETRISATION OF ELEMENTS ---
    double quadrupoleIntensity(1.2);
    double sextupoleIntensity(1);
    double curvatureDipole(1);
    double radius(0.1);
// ------------------------------------

    Vector3D endQuad1(3, 1.5, 0);
    Vector3D endSex1(3, 1, 0);
    Vector3D endSeg1(3, 0, 0);
    Vector3D endQuad2(3, -0.5, 0);
    Vector3D endSex2(3, -1, 0);
    Vector3D endSeg2(3, -2, 0);
    Vector3D endDip(2, -3, 0);

// --- PARAMETRISATION OF ACCELERATOR ---
    TextSupport s(cout);
    double dt(1e-11);
    double duration(1e-8);
    Accelerator accelerator(Vector3D(3, 2, 0));
// ------------------------------------

// --- CREATION OF ELEMENTS ---
    for (int i = 0; i < 4; ++i) {
        accelerator.addQuadrupole(endQuad1, radius, -quadrupoleIntensity);
        accelerator.addSextupole(endSex1, radius, sextupoleIntensity);
        accelerator.addSegment(endSeg1, radius);
        accelerator.addQuadrupole(endQuad2, radius, quadrupoleIntensity);
        accelerator.addSextupole(endSex2, radius, sextupoleIntensity);
        accelerator.addSegment(endSeg2, radius);
        accelerator.addDipole(endDip, radius, curvatureDipole, mass, charge, energy);

        endQuad1 = endQuad1 ^ Vector3D::e3;
        endSex1 = endSex1 ^ Vector3D::e3;
        endSeg1 = endSeg1 ^ Vector3D::e3;
        endQuad2 = endQuad2 ^ Vector3D::e3;
        endSex2 = endSex2 ^ Vector3D::e3;
        endSeg2 = endSeg2 ^ Vector3D::e3;
        endDip = endDip ^ Vector3D::e3;
    }
    accelerator.showElements(s.ostream());
// ------------------------------------

// --- CREATION OF PARTICLES ---
    accelerator.addCircularBeam(mass, charge, energy, Vector3D(0,-1,0), 1, 10, Vector3D(1, 1, 1), 0.0001);
// ------------------------------------

// --- SIMULATION ---
    for(size_t i(0); i < size_t(duration / dt) ; ++i){
        accelerator.evolve(dt);
        if(i % 100 == 0) {
            accelerator.draw(s);
        }
    }
// ------------------------------------


    return 0;
}
