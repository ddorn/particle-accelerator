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




    return 0;
};