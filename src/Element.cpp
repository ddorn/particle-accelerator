//
// Created by Gabin on 17.03.2019.
//

#include "..\header\Element.h"

bool Element::collideBorder(const Vector3D& position) const {
    Vector3D X(position - exit_);
    Vector3D direction(~(exit_ - entree_));
    return((X - (X * direction) * direction).normSquared() > radius_ * radius_);
}

bool Element::isOut(const Vector3D& position) const {
    Vector3D e3(0,0,1);
    return(e3.tripleProduct(position, exit_) > 0);
}
