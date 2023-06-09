//
// Created by Gabin on 18.03.2019.
//

#include "StraightElement.h"

using namespace std;



const RadialVec3D StraightElement::radialPosition(Vector3D pos) const {
    pos -= start();
    return RadialVec3D(pos * radial_direction,
                       pos * direction,
                       pos.z());
}

const RadialVec3D StraightElement::radialSpeed(const Vector3D &, const Vector3D &speed) const {
    return RadialVec3D(speed * radial_direction,
                       speed * direction,
                       speed.z());
}

const Vector3D StraightElement::absolutePosition(const RadialVec3D &pos) const {
    return start()
           + pos.r() * radial_direction
           + pos.s() * direction
           + pos.z() * Vector3D::e3;
}

const Vector3D StraightElement::absoluteSpeed(const RadialVec3D &, const RadialVec3D &speed) const {
    return speed.r() * radial_direction
           + speed.s() * direction
           + speed.z() * Vector3D::e3;
}

double StraightElement::length() const{
	return (exit() - start()).norm();
}
