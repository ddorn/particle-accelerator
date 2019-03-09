//
// Created by Gabin on 08.03.2019.
//
#include <iostream>
#include "../header/Particle.h"

using namespace std;



int main(){
    Vector3D position1(3.00984, -0.391837, 0);
    Vector3D momentum1(-210200, -2.64754e8, 0);
    Particle p(0.938272,(1.60217653e-19 / e), position1, momentum1);
    cout << p << endl;




    return 0;
};