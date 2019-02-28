
#ifndef PARTICLE_ACCELERATOR_VECTOR3D_H
#define PARTICLE_ACCELERATOR_VECTOR3D_H

#include <ostream>

typedef double component;

class Vector3D {
public:

    Vector3D() : x_(0), y_(0), z_(0) {}
    Vector3D(component x, component y, component z) : x_(x), y_(y), z_(z) {}

    component x() const { return x_; }
    component y() const { return y_; }
    component z() const { return z_; }

    component norm() const;
    component normSquared() const;
    component distanceTo(Vector3D) const;
    component unit() const;

    Vector3D cross(Vector3D) const;
    component dot(Vector3D) const;

    bool operator==(const Vector3D &rhs) const;
    bool operator!=(const Vector3D &rhs) const;
    Vector3D operator+(const Vector3D &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector3D &d);

private:
    component x_, y_, z_;

};


#endif //PARTICLE_ACCELERATOR_VECTOR3D_H
