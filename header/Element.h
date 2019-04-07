//
// Created by Gabin on 17.03.2019.
//

#ifndef PARTICLEACCELERATOR_ELEMENT_H
#define PARTICLEACCELERATOR_ELEMENT_H

#include "Vector3D.h"
#include "Content.h"

/**
 * RadialVec3D is a Vector3D used to represent coordinates
 * in the relative space of an element. It is almost a
 * cylindrical frame RSZ, but S is the distance along the
 * axis of the element, Z is the vertical direction and
 * R is the radial direction. R is the distance from the
 * center of curvature in case of a CurvedElement or from
 * the axis, in the XY plane for a StraitElement.
 */
class RadialVec3D : public Vector3D {
public:
    RadialVec3D() : Vector3D() {}
    RadialVec3D(component r, component s, component z) : Vector3D(r, s, z) {}
    component r() const { return x(); }
    component s() const { return y(); }
private:
    component x() const override { return Vector3D::x(); };
    component y() const override { return Vector3D::y(); };
};

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
    virtual const RadialVec3D radialPosition(const Vector3D& absolutePosition) const = 0;
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
    virtual const RadialVec3D radialPositionFromDistance(double l) const = 0;

    /**
     * Radius of the tube of the element.
     */
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
