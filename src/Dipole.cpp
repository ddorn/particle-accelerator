//
// Created by diego on 3/28/19.
//

#include "Dipole.h"

std::ostream &Dipole::print(std::ostream &os) const {
    CurvedElement::print(os);
    os << " - type : dipole" << std::endl;
    os << " - Magnetic field : " << magneticField_ << std::endl;
    return os;
}

const Vector3D Dipole::idealMagneticField(double mass, double charge, double energy) const {
    return curvature() * constants::C_PROTON * 1e9
    / constants::LIGHT_SPEED / charge
    * sqrt(energy * energy - mass * mass) * Vector3D::e3;
}