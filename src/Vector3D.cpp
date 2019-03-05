//
// Created by diego on 2/28/19.
//

#include <cmath>
#include "../header/Vector3D.h"

component Vector3D::precision(1e-6);


// Base functions on which other are based

Vector3D& Vector3D::operator+=(const Vector3D &rhs) {
    // We define it internally because is is very close to the class and we''l base other
    // functions on it (+)
    x_ += rhs.x();
    y_ += rhs.y();
    z_ += rhs.z();
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &rhs) {
    // I cannot find a way to express this function in terms of += without one unnecessary copy
    // Therefore, I prefer a little code repetition than un-efficient code.
    x_ -= rhs.x();
    y_ -= rhs.y();
    z_ -= rhs.z();
    return *this;
}

Vector3D &Vector3D::operator*=(const component &scalar) {
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;

    return *this;
}


bool operator==(const Vector3D& lhs, const Vector3D &rhs) {
    return fabs(lhs.x() - rhs.x()) < Vector3D::precision &&
           fabs(lhs.y() - rhs.y()) < Vector3D::precision &&
           fabs(lhs.z() - rhs.z()) < Vector3D::precision;
}
bool operator!=(const Vector3D &lhs, const Vector3D &rhs) { return !(lhs == rhs); }


// Mathematical operators

Vector3D operator-(Vector3D lhs, const Vector3D &rhs) { return lhs -= rhs; }
Vector3D operator+(Vector3D lhs, const Vector3D &rhs) { return lhs += rhs; }

Vector3D operator*(component scalar, Vector3D rhs) { return rhs *= scalar; }
Vector3D operator*(Vector3D lhs, component scalar) { return lhs *= scalar; }

Vector3D& operator/=(Vector3D &lhs, component scalar) { return lhs *= (1 / scalar); }
Vector3D operator/(Vector3D lhs, component scalar) { return lhs /= scalar; }

component Vector3D::norm() const {
    return sqrt(normSquared());
}
component Vector3D::normSquared() const {
    return x()*x() + y()*y() + z()*z();
}


std::ostream& operator<<(std::ostream &os, const Vector3D &d) {
    os << "Vector3D(" << d.x() << ", " << d.y() << ", " << d.z() << ")";
    return os;
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

