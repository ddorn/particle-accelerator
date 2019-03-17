/**
 * This header defines the constants namespace,
 * which has the universal constants useful for
 * or project.
 */

#ifndef PARTICLE_ACCELERATOR_CONSTANTS_H
#define PARTICLE_ACCELERATOR_CONSTANTS_H

namespace constants {
    /// Speed of light. Unit: c
    constexpr double LIGHT_SPEED(1.0);
    /// Speed of light squared. Unit: c²
    constexpr double LIGHT_SPEED_SQUARED(LIGHT_SPEED * LIGHT_SPEED);

    /// Charge of a proton. Unit: eV
    constexpr double PROTON_CHARGE(1.0);
    /// Mass of a proton. Unit: GeV/c^2
    constexpr double M_PROTON(0.938272);
    /// Mass of an electron. Unit: GeV/c²
    constexpr double M_ELECTRON(5.10999e-4);
}

#endif //PARTICLE_ACCELERATOR_CONSTANTS_H
