//
// Created by Gabin on 17.03.2019.
//

#include <iostream>
#include <Element.h>

#include "Element.h"
using namespace std;

bool Element::collideBorder(const Vector3D& position) const {
    Vector3D X(position - exit());
    Vector3D direction(~(exit() - entree()));
    return((X - (X * direction) * direction).normSquared() > radius() * radius());
}

bool Element::isOut(const Vector3D& position) const {
    Vector3D L(exit() - entree());
    Vector3D X(position - entree());
    return(X * L > L.normSquared());
}

const Vector3D &Element::entree() const {
    return entree_;
}

const Vector3D &Element::exit() const {
    return exit_;
}

double Element::radius() const {
    return radius_;
}

Element* Element::nextElement() const {
    return nextElement_;
}


std::ostream &operator<<(std::ostream &os, const Element &elem) {
    os << "Element :" << std::endl
       << " - entree : " << elem.entree() << std::endl
       << " - exit : " << elem.exit() << std::endl
       << " - radius : " << elem.radius() << std::endl;
    return os;
}
