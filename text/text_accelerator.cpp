//
// Created by diego on 3/17/19.
//

#include <iostream>
#include "TextSupport.h"
#include "Accelerator.h"
#include "constants.h"
#include "Dipole.h"
#include "CurvedElement.h"
#include "Segment.h"

using namespace constants;

int main() {
    TextSupport support(std::cout);
    Accelerator accelerator(&support);

    StraightElement* s = new Segment(Vector3D(1, 0, 0), Vector3D(2, 0, 0), 0.2, nullptr);
    Dipole* d = new Dipole(Vector3D(), Vector3D(1, 0, 0), 0.2, s, 0.3, 1);
    accelerator.add(d);


    accelerator.addParticle(M_PROTON, C_PROTON, Vector3D(1, 0, 0));

    accelerator.draw();
    while (!accelerator.beams().empty()) {
        accelerator.evolve();
        std::cout << "================" << std::endl;
        accelerator.draw();
    }

    return 0;
}
