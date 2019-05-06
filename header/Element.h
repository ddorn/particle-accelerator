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
    Vector3D start_;
    Vector3D exit_;
    double radius_;
    Element* nextElement_;
public:
    Element(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement)
    : start_(entree), exit_(exit), radius_(radius), nextElement_(nextElement) {}

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
     * @param pos of the particle
     */
    virtual bool isOut(Vector3D pos) const = 0;
    /**
     * Return the norm squared of the radial distance of the particle
     * relative to the ideal trajectory. Unit : m
     */
    virtual double radialDistanceSqrd(Vector3D pos) const = 0;
    /**
     * Return the norm squared of the component of the speed radial
     * relative to the ideal trajectory. Unit : m/s
     */
    virtual double length() const = 0;
    virtual double radialVelocitySqrd(const Vector3D& position, const Vector3D& speed) const = 0;

    // Coordinates change

    /**
     * Convert a position in the absolute space XYZ to the relative space RSZ of the element
     * @param absolutePosition Position in the accelerator
     * @return Radial
     */
    virtual const RadialVec3D radialPosition(Vector3D absolutePosition) const = 0;
    /**
     * Convert a speed expressed in the absolute coordinate space to the relative space RSZ
     * @param absolutePosition The position where the speed applies in the accelerator
     * @param absoluteSpeed The speed in XYZ coordinates
     * @return The speed in the relative space
     */
    virtual const RadialVec3D radialSpeed(const Vector3D& absolutePosition, const Vector3D& absoluteSpeed) const = 0;
    /**
     * Convert a position in the relative space coordinate RSZ of the element to
     * the absolute space XYZ of the accelerator
     * @param radialPos the coordinates in the RSZ vector space
     * @return The vector in the accelerator's frame
     */
    virtual const Vector3D absolutePosition(const RadialVec3D &radialPos) const = 0;
    /**
     * Convert a RSZ speed to an absolute one
     * @param relativePosition Where the speed applies
     * @param relativeSpeed The RSZ speed
     * @return A XYZ speed
     */
    virtual const Vector3D absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const = 0;
//    virtual const RadialVec3D radialPositionFromDistance(double l) const = 0;

    /**
     * Radius of the tube of the element.
     */
    double radius() const { return radius_; }
    const Vector3D &start() const { return start_; }
    const Vector3D &exit() const { return exit_; }
    Element* nextElement() const { return nextElement_; }

    void setNextElement(Element* e) { nextElement_ = e; }

    /**
     * Print info of the element on the stream.
     * @param os The stream to write the element to
     * @return the same stream.
     * @note we add this to allow for polymorphic printing of elements,
     *      but one should just use << as usual to write and element.
     */
    virtual std::ostream& print(std::ostream &os) const;

    void draw(Support &support) const override { support.draw(*this); }
};

std::ostream& operator<<(std::ostream &os, const Element &elem);

#endif //PARTICLEACCELERATOR_ELEMENT_H
