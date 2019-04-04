//
// Created by Gabin on 17.03.2019.
//

#ifndef PARTICLEACCELERATOR_ELEMENT_H
#define PARTICLEACCELERATOR_ELEMENT_H


#include "Vector3D.h"
#include "Content.h"

class Particle;

class Element : public Content {
private:
    Vector3D entree_;
    Vector3D exit_;
    double radius_;
    Element* nextElement_;
public:
    Element(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement)
    : entree_(entree), exit_(exit), radius_(radius), nextElement_(nextElement) {}

    /**
     * Get the magnetic fields at a given point in space.
     * @param position A point in absolute space coordinate.
     * @return The magnetic field.
     */
    virtual const Vector3D magneticForceAt(const Vector3D & position) const = 0;
    /**
     * Test whether or not the particle collided
     * with the border
     * @param position of the particle
     */
    virtual bool collideBorder(const Vector3D& position) const = 0;
    /**
     * Test whether or not the particle is in
     * the next element.
     * @param position of the particle
     */
    virtual bool isOut(const Vector3D& position) const = 0;

    double radius() const;
    const Vector3D &entree() const;
    const Vector3D &exit() const;

    Element* nextElement() const;
    void setNextElement(Element* e) { nextElement_ = e; }

    /**
     * Print info of the element on the stream.
     * @param os The stream to write the element to
     * @return the same stream.
     * @note we add the to allow for polymorphic printing of elements,
     *      but one should just use << as usual to write and element.
     */
    virtual std::ostream& print(std::ostream &os) const;

    void draw(Support &support) const override { support.draw(*this); }
};

std::ostream& operator<<(std::ostream &os, const Element &elem);

#endif //PARTICLEACCELERATOR_ELEMENT_H
