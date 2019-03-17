//
// Created by Gabin on 08.03.2019.
//

#ifndef PARTICLE_ACCELERATOR_CONSTANTS_H
#define PARTICLE_ACCELERATOR_CONSTANTS_H

namespace constants {
    constexpr double LIGHT_SPEED(1.0); // speed of light, unit : LIGHT_SPEED
    constexpr double LIGHT_SPEED_SQUARED(LIGHT_SPEED * LIGHT_SPEED);

    constexpr double PROTON_CHARGE(1.0); //charge of a proton
    constexpr double M_PROTON(0.938272); // Mass of a proton in GeV/c²
    constexpr double M_ELECTRON(5.10999e-4); // Mass of an electron in GeV/c²
}

#endif //PARTICLE_ACCELERATOR_CONSTANTS_H
