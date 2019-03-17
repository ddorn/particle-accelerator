//
// Created by Gabin on 08.03.2019.
//
#include <iostream>
#include "../header/Particle.h"

using namespace std;
using namespace constants;


int main(){
    Vector3D position1(3.00984, -0.391837, 0);
    Vector3D momentum1(-0.0014023, -1.76625, 0);
    Particle p(M_PROTON, PROTON_CHARGE, position1, momentum1);
    cout << p << endl;

    Vector3D magnetic_field(0, 0, 7);
    double dt(9e-4);
    cout << "Ajout d'une force magnétique " << magnetic_field << "(dt = " << dt << ")" << endl;
//    p.addMagneticForce(magnetic_field, dt);
    for (int i = 0; i < 1; ++i) {
        p.addMagneticForce(magnetic_field, dt);
        p.evolve(1);
    }

    cout << p << endl;

    Particle p2(M_PROTON, PROTON_CHARGE, Vector3D(0, 0, 0), Vector3D(0.6, 0.5, 0));
    cout << p2 << endl;
    for (int j = 0; j < 10000; ++j) {
        p2.addMagneticForce(Vector3D(0, 0, 4), 0.01);
        p2.evolve(1e-2);
    }
    cout << p2 << endl;
    cout << "gamma should be 1,30112" << endl;
    cout << "gamma is        " << p2.gamma() << endl;


    return 0;
};