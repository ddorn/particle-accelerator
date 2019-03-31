//
// Created by Gabin on 17.03.2019.
//

#ifndef PARTICLEACCELERATOR_ELEMENT_H
#define PARTICLEACCELERATOR_ELEMENT_H


#include "Vector3D.h"

class Particle;

class Element{
private:
    Vector3D entree_;
    Vector3D exit_;
    double radius_;
    Element* nextElement_;
public:
    Element(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement) : entree_(
            entree), exit_(exit), radius_(radius), nextElement_(nextElement) {}

    virtual const Vector3D magneticForceAt(const Vector3D & /*position*/) const { return Vector3D(); }
    /**
     * Test whether or not the particle collided
     * with the border
     * @param position of the particle
     */
    bool collideBorder(const Vector3D& position) const;
    /**
     * Test whether or not the particle is in
     * the next element.
     * @param position of the particle
     */
    bool isOut(const Vector3D& position) const;

    double radius() const;
    const Vector3D &entree() const;
    const Vector3D &exit() const;

    Element* nextElement() const;
};

std::ostream& operator<<(std::ostream &os, const Element &elem);

#endif //PARTICLEACCELERATOR_ELEMENT_H
