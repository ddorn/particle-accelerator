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

    accelerator.add(new Dipole(Vector3D(), Vector3D(1, 0, 0), 0.2, nullptr, 0.3, Vector3D(0, 0, 1)));
    accelerator.addParticle(M_PROTON, PROTON_CHARGE, Vector3D(1, 0, 0));

    accelerator.draw();
    while (!accelerator.particles().empty()) {
        accelerator.evolve();
        std::cout << "================" << std::endl;
        accelerator.draw();
    }

    return 0;
}
