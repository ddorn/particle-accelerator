
#ifndef PARTICLE_ACCELERATOR_VECTOR3D_H
#define PARTICLE_ACCELERATOR_VECTOR3D_H

#include <ostream>

typedef double component;

class Vector3D {
public:
    // We leave it public as one may want to know what is the precision of the calculations or change it.
    static component precision;

    Vector3D() : x_(0), y_(0), z_(0) {}
    Vector3D(component x, component y, component z) : x_(x), y_(y), z_(z) {}

    component x() const { return x_; }
    component y() const { return y_; }
    component z() const { return z_; }

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
     * @todo Should this be a class method that we would call Vector3D::tripleProduct(a, b, c)
     *        I think it would make more sense as it's not the particularity of a vector
     */
    component tripleProduct(const Vector3D&, const Vector3D&) const;

    Vector3D& operator+=(const Vector3D& rhs);
    Vector3D& operator-=(const Vector3D& rhs);
    Vector3D& operator*=(const component& scalar);

private:
    component x_, y_, z_;
};

// Mathematical operations

Vector3D operator*(component scalar, Vector3D rhs);
Vector3D operator*(Vector3D lhs, component scalar);
Vector3D operator/(Vector3D lhs, component scalar);
Vector3D& operator/=(Vector3D &lhs, component scalar);

Vector3D operator+(Vector3D lhs, const Vector3D &rhs);
Vector3D operator-(Vector3D lhs, const Vector3D &rhs);
Vector3D operator-(Vector3D const&);

/**
 * Cross product between two Vector3D
 * @return A Vector orthogonal to both vectors.
 */
Vector3D operator^(Vector3D const& lhs, Vector3D const& rhs);
/**
 * Dot product between two Vector3D
 * @return The area between the two vectors.
 */
component operator*(Vector3D const&, const Vector3D& rhs);
/**
 * Get a unit vector pointing in the same direction.
 * @return A vector of norm 1
 */
Vector3D operator~(Vector3D);

bool operator==(const Vector3D&, const Vector3D&);
bool operator!=(const Vector3D &lhs, const Vector3D &rhs);

std::ostream& operator<<(std::ostream &os, const Vector3D &vec);

#endif //PARTICLE_ACCELERATOR_VECTOR3D_H
