/**
 * This header defines the constants namespace,
 * which has the universal constants useful for
 * our project.
 */

#ifndef PARTICLE_ACCELERATOR_CONSTANTS_H
#define PARTICLE_ACCELERATOR_CONSTANTS_H

namespace constants {
    /// Speed of light. Unit: m/s
    constexpr double LIGHT_SPEED(299792458);
    /// Speed of light squared. Unit: m²/s²
    constexpr double LIGHT_SPEED_SQUARED(LIGHT_SPEED * LIGHT_SPEED);
    /// Charge of a proton. Unit: Coulomb
    constexpr double C_PROTON(1.60217653e-19);
    /// Mass of a proton. Unit: GeV/c^2
    constexpr double M_PROTON(0.938272);
    /// Mass of an electron. Unit: GeV/c²
    constexpr double M_ELECTRON(5.10999e-4);
    /// Charge of an electron. Unit: Coulomb
    constexpr double C_ELECTRON(-1.60217653e-19);
    /// Kilogram. Unit : GeV / c^2
    constexpr double KG(LIGHT_SPEED_SQUARED / C_PROTON / 1e9);
    /// vacuum permittivity : Farads / m
    constexpr double VACUUM_PERMITTIVITY(8.854187817 * 1e-12);
}

#endif //PARTICLE_ACCELERATOR_CONSTANTS_H
