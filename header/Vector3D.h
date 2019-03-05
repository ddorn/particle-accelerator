
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

    component norm() const;
    component normSquared() const;
    component distanceTo(const Vector3D&) const;
    const Vector3D unit() const;
    const Vector3D opposite() const;

    const Vector3D cross(const Vector3D&) const;
    const Vector3D operator^(const Vector3D&) const;
    component dot(const Vector3D&) const;
    component operator*(const Vector3D& rhs) const;
    component tripleProduct(const Vector3D&, const Vector3D&) const;

    const Vector3D operator-() const;

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

bool operator==(const Vector3D&, const Vector3D&);
bool operator!=(const Vector3D &lhs, const Vector3D &rhs);
std::ostream& operator<<(std::ostream &os, const Vector3D &vec);

#endif //PARTICLE_ACCELERATOR_VECTOR3D_H
