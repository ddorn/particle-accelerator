//
// Created by diego on 3/28/19.
//

#include "Dipole.h"

std::ostream &Dipole::print(std::ostream &os) const {
    CurvedElement::print(os);
    os << " - Magnetic field : " << magneticField_ << std::endl;
    return os;
}
