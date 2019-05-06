/**
 * This header defines the constants namespace,
 * which has the universal constants useful for
 * our project.
 */

#ifndef PARTICLE_ACCELERATOR_CONSTANTS_H
#define PARTICLE_ACCELERATOR_CONSTANTS_H

namespace constants {
    /// Speed of light. Unit: c
    constexpr double LIGHT_SPEED(1.0);
    /// Speed of light squared. Unit: c²
    constexpr double LIGHT_SPEED_SQUARED(LIGHT_SPEED * LIGHT_SPEED);
    constexpr double LIGHT_SPEED_MS(299792458);
    /// Charge of a proton. Unit: eV
    constexpr double PROTON_CHARGE(1.0);
    /// Charge of a proton. Unit: C
    constexpr double C_PROTON_COULOMB(1.60217653e-19);
    /// Mass of a proton. Unit: GeV/c^2
    constexpr double M_PROTON(0.938272);
    /// Mass of an electron. Unit: GeV/c²
    constexpr double M_ELECTRON(5.10999e-4);
    /// Kilogram. Unit : GeV / c^2
    constexpr double KG(LIGHT_SPEED_MS * LIGHT_SPEED_MS / C_PROTON_COULOMB / 1e9);
    /// Coulomb. Unit : charge of a proton.
    constexpr double COULOMB(1/C_PROTON_COULOMB);
}

#endif //PARTICLE_ACCELERATOR_CONSTANTS_H
