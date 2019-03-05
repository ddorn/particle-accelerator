//
// Created by diego on 2/28/19.
//

#include <cmath>
#include "../header/Vector3D.h"

component Vector3D::precision(1e-6);

component Vector3D::norm() const {
    return sqrt(normSquared());
}

component Vector3D::normSquared() const {
    return x()*x() + y()*y() + z()*z();
}

bool Vector3D::operator==(const Vector3D &rhs) const {
    return fabs(x() - rhs.x()) < precision &&
           fabs(y() - rhs.y()) < precision &&
           fabs(z() - rhs.z()) < precision;
}

bool Vector3D::operator!=(const Vector3D &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Vector3D &d) {
    os << "Vector3D(" << d.x() << ", " << d.y() << ", " << d.z() << ")";
    return os;
}

const Vector3D operator*(component scalar, const Vector3D &rhs) {
    return rhs*scalar;
}

const Vector3D Vector3D::operator+(const Vector3D &rhs) const {
    return Vector3D(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
}

const Vector3D Vector3D::operator-(const Vector3D &rhs) const {
    return Vector3D(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
}




component Vector3D::distanceTo(const Vector3D &other) const {
    return (*this - other).norm();
}

const Vector3D Vector3D::unit() const {
    return *this / norm();
}

const Vector3D Vector3D::opposite() const {
    return Vector3D(-x(),-y(),-z());
}

const Vector3D Vector3D::operator*(const component &scalar) const {
    return Vector3D(x() * scalar, y() * scalar, z() * scalar);
}

const Vector3D Vector3D::operator/(const component &scalar) const {
    // scalar could be 0, but it will throw the right error, so we don't do anything to prevent this
    return (*this) * (1 / scalar);
}

component Vector3D::dot(const Vector3D &rhs) const {
    return x() * rhs.x() + y() * rhs.y() + z() * rhs.z();
}

component Vector3D::operator*(const Vector3D &rhs) const {
    return dot(rhs);
}

const Vector3D Vector3D::cross(const Vector3D &rhs) const {
    return Vector3D(y() * rhs.z() - z() * rhs.y(), z() * rhs.x() - x() * rhs.z(), x() * rhs.y() - y() * rhs.x());
}

const Vector3D Vector3D::operator^(const Vector3D & rhs) const {
    return cross(rhs);
}

const Vector3D Vector3D::operator-() const {
    return opposite();
}

component Vector3D::tripleProduct(const Vector3D &v, const Vector3D &w) const {
    return (*this) * (v ^ w);
}




