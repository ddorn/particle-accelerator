//
// Created by Gabin on 17.03.2019.
//

#include <iostream>
#include <typeinfo>       // operator typeid
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

std::ostream &Element::print(std::ostream &os) const {
    // typeid(...).name() gives the name of an object so we don't
    // have to change this line when overriding
    os << typeid(*this).name() << " :" << std::endl
       << " - entree : " << entree() << std::endl
       << " - exit : " << exit() << std::endl
       << " - radius : " << radius() << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Element &elem) { return elem.print(os); }
