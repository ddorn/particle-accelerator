//
// Created by Gabin on 31.03.2019.
//

#include "Segment.h"

std::ostream& Segment::print(std::ostream &os) const {
    StraightElement::print(os);
    os << " type : segment" << std::endl;
    return os;
}
