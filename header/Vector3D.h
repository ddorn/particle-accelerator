
#ifndef PARTICLE_ACCELERATOR_VECTOR3D_H
#define PARTICLE_ACCELERATOR_VECTOR3D_H

#include <iostream>
#include "Content.h"
#include "Support.h"

typedef double component;

class Vector3D : Content {
public:
    static const Vector3D e1;
    static const Vector3D e2;
    static const Vector3D e3;

    Vector3D() : x_(0), y_(0), z_(0) {}
    Vector3D(component x, component y, component z) : x_(x), y_(y), z_(z) {}

    virtual component x() const { return x_; }

    virtual component y() const { return y_; }

    virtual component z() const { return z_; }

    static component getPrecision();
    static void setPrecision(component);

    /**
     * Convenient way to check if a vector is the null vector.
     * This returns true for very small vectors.
     * @return Whether the vector is 0.
     */
    bool isZero() const;
    /**
     * The norm of a vector.
     * @related normSquared
     * @return The length of the vector.
     */
    component norm() const;
    /**
     * The squared norm of a vector, which is faster than norm as it doesn't use a sqrt.
     * @return The length of the vector, squared
     */
    component normSquared() const;
    /**
     * Get the distance to another point in space.
     * @param other The second point
     * @return The cartesian distance between both points.
     */
    component distanceTo(const Vector3D&) const;
    /**
     * The triple product between three vectors
     * @return The signed volume covered by the three vectors.
     */
    component tripleProduct(const Vector3D&, const Vector3D&) const;

    /**
     * Get a rotated version of the vector, rotated by angle around axis
     * @param axis A vector around which to rotate the vector.
     * @param angle in radians
     * @return The rotated vector
     */
    Vector3D rotate(const Vector3D &axis, double angle) const;

    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D& operator-=(const Vector3D& rhs);
    Vector3D& operator*=(const component& scalar);

    void draw(Support &support) const override { support.draw(*this); }

private:

    static component precision;
    component x_, y_, z_;
};

// Mathematical operations

const Vector3D operator*(component scalar, Vector3D rhs);
const Vector3D operator*(Vector3D lhs, component scalar);
const Vector3D operator/(Vector3D lhs, component scalar);
Vector3D& operator/=(Vector3D &lhs, component scalar);

const Vector3D operator+(Vector3D lhs, const Vector3D &rhs);
const Vector3D operator-(Vector3D lhs, const Vector3D &rhs);
const Vector3D operator-(Vector3D const&);

/**
 * Cross product between two Vector3D
 * @return A Vector orthogonal to both vectors.
 */
const Vector3D operator^(Vector3D const& lhs, Vector3D const& rhs);
/**
 * Dot product between two Vector3D
 * @return The area between the two vectors.
 */
component operator*(Vector3D const&, const Vector3D& rhs);
/**
 * Get a unit vector pointing in the same direction.
 * @return A vector of norm 1
 */
const Vector3D operator~(Vector3D);
/**
 * Test wether two vectors are equal
 * If the difference between two components is
 * less than the precision attribute, it is considered
 * equal.
 * @return
 */
bool operator==(const Vector3D&, const Vector3D&);
bool operator!=(const Vector3D &lhs, const Vector3D &rhs);

std::ostream& operator<<(std::ostream &os, const Vector3D &vec);


/**
 * RadialVec3D is a simpler Vector3D used to represent coordinates
 * in the relative space of an element. It is almost a
 * cylindrical frame RSZ, but S is the distance along the
 * axis of the element, Z is the vertical direction and
 * R is the radial direction. R is the distance from the
 * center of curvature in case of a CurvedElement or from
 * the axis, in the XY plane for a StraitElement.
 *
 * Note that it is not a vector space with the same operation of
 * the Vector3D so it make no sense to inherit Vector3D, and we
 * have no need for the operations (+, *, ...) in our code
 */
class RadialVec3D {
public:
    RadialVec3D() : r_(0), s_(0), z_(0) {}
    RadialVec3D(component r, component s, component z) : r_(r), s_(s), z_(z) {}
    component r() const { return r_; }
    component s() const { return s_; }
    component z() const { return z_; }
private:
    component r_;
    component s_;
    component z_;
};
std::ostream& operator<<(std::ostream &os, const RadialVec3D &vec);


#endif //PARTICLE_ACCELERATOR_VECTOR3D_H
