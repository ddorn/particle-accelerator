//
// Created by diego on 3/31/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"

using namespace std;

int main() {
    TextSupport s(cout);
    Accelerator bobLEponge(Vector3D(0, 3, 0));

    double radius(0.1);
    Vector3D pqf(1, 3, 0);
    Vector3D pd1(2, 3, 0);
    Vector3D pd(3, 2, 0);
    Vector3D pqd(3, 1, 0);
    Vector3D pd2(3, 0, 0);

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
    bobLEponge.draw(s);
    for (int j = 0; j < 10; ++j) {
        bobLEponge.evolve();
        bobLEponge.draw(s);
    }
    return 0;
}