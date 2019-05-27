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

std::ostream &operator<<(std::ostream &os, const Element &elem) { return elem.print(os); }
