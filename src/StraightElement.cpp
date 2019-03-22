//
// Created by Gabin on 18.03.2019.
//

#include "StraightElement.h"

std::ostream &operator<<(std::ostream &os, const StraightElement &elem) {
    os << "Straight element :" << std::endl
        << " - entree : " << elem.entree() << std::endl
        << " - exit : " << elem.exit() << std::endl
        << " - radius : " << elem.radius() << std::endl;
    return os;
}

