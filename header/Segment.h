//
// Created by Gabin on 31.03.2019.
//

#ifndef PARTICLEACCELERATOR_SEGMENT_H
#define PARTICLEACCELERATOR_SEGMENT_H


#include "Vector3D.h"
#include "Particle.h"
#include "StraightElement.h"
#include "Element.h"

class Segment : public StraightElement{

public:
    Segment(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement)
            : StraightElement(entree, exit, radius, nextElement) {}
    /**
     * Segment applies no magnetic force
     * It returns a null vector.
     */
    const Vector3D magneticForceAt(const Vector3D & /*position*/) const override { return Vector3D(); }
    std::ostream& print(std::ostream &os) const override;
    void draw(Support &support) const override { support.draw(*this); }

};


#endif //PARTICLEACCELERATOR_SEGMENT_H
