//
// Created by Gabin on 31.03.2019.
//

#include "Quadrupole.h"

const Vector3D Quadrupole::magneticForceAt(const Vector3D & position) const {
    RadialVec3D relativePos = radialPosition(position);
    return intensity_ * (relativePos.r() * Vector3D::e3
                         + relativePos.z() * radial_direction);
}

std::ostream &Quadrupole::print(std::ostream &os) const {
    Element::print(os);
    os << " - type : quadrupole" << std::endl;
    return os;
}