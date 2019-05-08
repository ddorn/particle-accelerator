//
// Created by diego on 5/8/19.
//

#include "Sextupole.h"

Sextupole::Sextupole(const Vector3D &start, const Vector3D &exit, double radius, Element *nextElement, double intensity)
        : StraightElement(start, exit, radius, nextElement), intensity_(intensity){}

const Vector3D Sextupole::magneticForceAt(const Vector3D &position) const {
    RadialVec3D pos = radialPosition(position);
    RadialVec3D b(intensity_ * pos.r() * pos.z(),
                    0, intensity_ * (pos.r() * pos.r() - pos.z() * pos.z()) / 2.0);
    return absoluteSpeed(pos, b);
}
