//
// Created by diego on 3/17/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include "constants.h"

using namespace constants;

int main() {
    TextSupport support(std::cout);
    Accelerator accelerator(&support);

    accelerator.add(Particle(M_PROTON, PROTON_CHARGE, Vector3D(), Vector3D(1, 0, 0)));

    accelerator.evolve();
    accelerator.draw();
    accelerator.evolve();
    accelerator.draw();

    return 0;
}