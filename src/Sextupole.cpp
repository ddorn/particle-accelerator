//
// Created by diego on 5/8/19.
//

#include <Sextupole.h>

#include "Sextupole.h"


const Vector3D Sextupole::magneticForceAt(const Vector3D &position) const {
    RadialVec3D pos = radialPosition(position);
    RadialVec3D b(intensity_ * pos.r() * pos.z(),
                    0, intensity_ * (pos.r() * pos.r() - pos.z() * pos.z()) / 2.0);
    return absoluteSpeed(pos, b);
}

std::ostream &Sextupole::print(std::ostream &os) const {
    Element::print(os);
    os << " - type : sextupole" << std::endl
    << " - magnetic intensity : " << this->intensity_ << std::endl;
    return os;
}
