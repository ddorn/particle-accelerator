//
// Created by Gabin on 17.03.2019.
//

#include "..\header\Element.h"

bool Element::collideBorder(const Vector3D& position) const {
    Vector3D X(position - exit());
    Vector3D direction(~(exit() - entree()));
    return((X - (X * direction) * direction).normSquared() > radius() * radius());
}

bool Element::isOut(const Vector3D& position) const {
    Vector3D e3(0,0,1);
    return(e3.tripleProduct(position, exit()) > 0);
}

const Vector3D &Element::entree() const {
    return entree_;
}

const Vector3D &Element::exit() const {
    return exit_;
}

const Vector3D &Element::radius() const {
    return radius_;
}

Element *Element::nextElement() const {
    return nextElement_;
}
