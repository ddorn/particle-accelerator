//
// Created by Gabin on 18.03.2019.
//

#include "StraightElement.h"


bool StraightElement::collideBorder(const Vector3D& position) const {
    Vector3D X(position - exit());
    Vector3D direction(~(exit() - entree()));
    return((X - (X * direction) * direction).normSquared() > radius() * radius());
}

bool StraightElement::isOut(const Vector3D& position) const {
    Vector3D L(exit() - entree());
    Vector3D X(position - entree());
    return(X * L > L.normSquared());
}