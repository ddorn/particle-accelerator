//
// Created by Gabin on 18.03.2019.
//

#include "StraightElement.h"


bool StraightElement::collideBorder(const Vector3D& position) const {
    return radialDistanceSqrd(position) > radius() * radius();
}

bool StraightElement::isOut(const Vector3D& position) const {
    Vector3D L(exit() - entree());
    Vector3D X(position - entree());
    return(X * L > L.normSquared());
}

double StraightElement::radialDistanceSqrd(const Vector3D &position) const {
    Vector3D X(position - exit());
    Vector3D direction(~(exit() - entree()));
    return (X - (X * direction) * direction).normSquared();
}

double StraightElement::radialVelocitySqrd(const Vector3D &, const Vector3D &speed) const {
    Vector3D direction(~(exit() - entree()));
    return (speed - (speed * direction) * direction).normSquared();
}

const RadialVec3D StraightElement::radialPosition(const Vector3D &pos) const {
    Vector3D dir = ~(exit() - entree());
    Vector3D rel = pos - entree();
    return RadialVec3D(rel * (Vector3D::e3 ^ dir), rel * dir, rel.z());
}

const RadialVec3D StraightElement::radialSpeed(const Vector3D &, const Vector3D &speed) const {
    Vector3D dir = ~(exit() - entree());
    return RadialVec3D(speed * (Vector3D::e3 ^ dir), speed * dir, speed.z());
}

const Vector3D StraightElement::absolutePosition(const RadialVec3D &pos) const {
    Vector3D dir = ~(exit() - entree());
    Vector3D normal = Vector3D::e3 ^ dir;
    return entree() + pos.r() * normal + pos.s() * dir + pos.z() * Vector3D::e3;
}

const Vector3D StraightElement::absoluteSpeed(const RadialVec3D &, const RadialVec3D &speed) const {
    Vector3D dir = ~(exit() - entree());
    Vector3D normal = Vector3D::e3 ^ dir;
    return speed.r() * normal + speed.s() * dir + speed.z() * Vector3D::e3;
}
