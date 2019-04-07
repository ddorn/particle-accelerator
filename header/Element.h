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
    /**
     * Return the norm squared of the radial distance of the particle
     * relative to the ideal trajectory. Unit : c * s
     */
    virtual double radialDistanceSqrd(const Vector3D& position) const = 0;
    /**
     * Return the norm squared of the component of the speed radial
     * relative to the ideal trajectory. Unit : c
     */
    virtual double length() const = 0;
    virtual double radialVelocitySqrd(const Vector3D& position, const Vector3D& speed) const = 0;

    // Coordinates change
    
    /**
     * Convert a position in the absolute space XYZ to the relative space RSZ of the element
     * @param absolutePosition Position in the accelerator
     * @return Radial
     */
    virtual const Vector3D radialPosition(const Vector3D& absolutePosition) const = 0;
    virtual const Vector3D radialSpeed(const Vector3D& absolutePosition, const Vector3D& absoluteSpeed) const = 0;
    virtual const Vector3D absolutePosition(const Vector3D &radialPos) const = 0;
    virtual const Vector3D absoluteSpeed(const Vector3D &relativePosition, const Vector3D &relativeSpeed) const = 0;
    virtual const Vector3D radialPositionFromDistance(double l) const = 0;

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
