//
// Created by Gabin on 18.03.2019.
//

#include <StraightElement.h>

#include "StraightElement.h"


bool StraightElement::collideBorder(const Vector3D& position) const {
    return(radialDistanceSqrd(position) > radius() * radius());
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

double StraightElement::radialVelocitySqrd(const Vector3D &position, const Vector3D &speed) const {
    Vector3D direction(~(exit() - entree()));
    return (speed - (speed * direction) * direction).normSquared();
}
