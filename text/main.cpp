//
// Created by diego on 3/17/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include "constants.h"
#include "Dipole.h"
#include "CurvedElement.h"

using namespace constants;

int main() {
    TextSupport support(std::cout);
    Accelerator accelerator(&support);

    accelerator.add(new Particle(M_PROTON, PROTON_CHARGE, Vector3D(), Vector3D(1, 0, 0)));
    accelerator.add(new Dipole(Vector3D(), Vector3D(0, 0, 1), 0.2, nullptr, 42, Vector3D(69, 69, 69)));
    accelerator.evolve();
    accelerator.draw();
    accelerator.evolve();
    accelerator.draw();

    return 0;
}
