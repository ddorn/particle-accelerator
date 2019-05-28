//
// Created by Gabin on 17.03.2019.
//

#include <iostream>
#include <typeinfo>       // operator typeid

#include "Element.h"

using namespace std;

std::ostream &Element::print(std::ostream &os) const {
    // typeid(...).name() gives the name of an object so we don't
    // have to change this line when overriding
    os << "Element :" << std::endl
       << " - start : " << start() << std::endl
       << " - exit : " << exit() << std::endl
       << " - radius : " << radius() << std::endl;
    return os;
}

bool Element::isOut(const Vector3D& pos, bool clockwise) const {
    if (clockwise) return Vector3D::e3.tripleProduct(pos, exit()) > 0;
    else return Vector3D::e3.tripleProduct(pos, start()) < 0;
//    if (clockwise) return radialPosition(pos).s() > length();
//    else return radialPosition(pos).s() < 0;
}

bool Element::collideBorder(const Vector3D &position) const {
    RadialVec3D rad(radialPosition(position));
    return rad.r() * rad.r() + rad.z() * rad.z() > radius() * radius();
}

std::ostream &operator<<(std::ostream &os, const Element &elem) { return elem.print(os); }
