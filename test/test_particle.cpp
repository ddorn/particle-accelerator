//
// Created by Gabin on 08.03.2019.
//
#include <iostream>
#include "../header/Particle.h"

using namespace std;
using namespace constants;


int main(){
    Vector3D speed1(-210200, -2.64754e08, 0);
    Vector3D speed2(210200, - 2.64754e08, 0);
    double gamma(2.13158);
    double mass(M_PROTON);
    Vector3D momentum1(speed1 * gamma * mass / KG);
    Vector3D momentum2(speed2 * gamma * mass / KG);
    Vector3D position1(3.00984, -0.391837, 0);
    Vector3D position2(2.99016, -0.391837, 0);
    Particle p(M_PROTON, C_PROTON, position1, momentum1, <#initializer#>, nullptr, <#initializer#>);
    cout << p << endl;

    Vector3D magnetic_field(0, 0, 7);
    double dt(1e-11);


    cout << "Ajout d'une force magnétique " << magnetic_field << "(dt = " << dt << ")" << endl;
//    p.addMagneticForce(magnetic_field, dt);
    for (int i = 0; i < 1; ++i) {
        p.addMagneticForce(magnetic_field, dt);
        p.evolve(dt);
    }

    cout << p << endl;

    Particle p2(M_PROTON, C_PROTON, position2, momentum2, <#initializer#>, nullptr, <#initializer#>);
    cout << p2 << endl;
    for (int j = 0; j < 1; ++j) {
        p2.addMagneticForce(magnetic_field, dt);
        p2.evolve(dt);
    }
    cout << p2 << endl;
    cout << "gamma should be 2.13158" << endl;
    cout << "gamma is        " << p2.gamma() << endl;


    return 0;
};