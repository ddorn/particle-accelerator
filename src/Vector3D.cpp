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

Vector3D& Vector3D::operator*=(const component &scalar) {
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


const Vector3D operator-(Vector3D lhs, const Vector3D &rhs) { return lhs -= rhs; }
const Vector3D operator-(Vector3D const& vec) { return Vector3D(-vec.x(), -vec.y(), -vec.z()); }
const Vector3D operator+(Vector3D lhs, const Vector3D &rhs) { return lhs += rhs; }

const Vector3D operator*(component scalar, Vector3D rhs) { return rhs *= scalar; }
const Vector3D operator*(Vector3D lhs, component scalar) { return lhs *= scalar; }

Vector3D& operator/=(Vector3D &lhs, component scalar) { return lhs *= (1 / scalar); }
const Vector3D operator/(Vector3D lhs, component scalar) { return lhs /= scalar; }

component operator*(Vector3D const& lhs, const Vector3D &rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}
const Vector3D operator^(Vector3D const& lhs, const Vector3D & rhs) {
    return Vector3D(
            lhs.y() * rhs.z() - lhs.z() * rhs.y(),
            lhs.z() * rhs.x() - lhs.x() * rhs.z(),
            lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

const Vector3D operator~(Vector3D vec) {
    // TODO: What about when the vector is (0, 0, 0) ? Shall we return \vec{0} or throw an exception ?
    return vec /= vec.norm();
}

component Vector3D::tripleProduct( Vector3D const& v, const Vector3D &w) const {
    return (*this) * (v ^ w);
}


// Printing


std::ostream& operator<<(std::ostream &os, const Vector3D &d) {
    os << "Vector3D(" << d.x() << ", " << d.y() << ", " << d.z() << ")";
    return os;
}

// Norm


component Vector3D::norm() const { return sqrt(normSquared()); }
component Vector3D::normSquared() const { return x()*x() + y()*y() + z()*z(); }
component Vector3D::distanceTo(const Vector3D &other) const { return (*this - other).norm(); }
