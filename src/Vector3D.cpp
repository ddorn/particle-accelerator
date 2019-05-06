//
// Created by diego on 2/28/19.
//

#include <cmath>
#include <iostream>
#include "Vector3D.h"

const Vector3D Vector3D::e1(1,0,0);
const Vector3D Vector3D::e2(0,1,0);
const Vector3D Vector3D::e3(0,0,1);


component Vector3D::precision(1e-24);
component Vector3D::getPrecision() { return precision; }
void Vector3D::setPrecision(component newPrecision) { if(newPrecision > 0) precision = newPrecision;}

// Base functions on which other are based


Vector3D& Vector3D::operator+=(const Vector3D &rhs) {
    // We define it internally because is is very close to the class and we'll base other
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
    return fabs(lhs.x() - rhs.x()) < Vector3D::getPrecision() &&
           fabs(lhs.y() - rhs.y()) < Vector3D::getPrecision() &&
           fabs(lhs.z() - rhs.z()) < Vector3D::getPrecision();
}
bool operator!=(const Vector3D &lhs, const Vector3D &rhs) { return !(lhs == rhs); }


// Mathematical operators


const Vector3D operator-(Vector3D lhs, const Vector3D &rhs) { return lhs -= rhs; }
const Vector3D operator-(Vector3D const& vec) { return Vector3D(-vec.x(), -vec.y(), -vec.z()); }
const Vector3D operator+(Vector3D lhs, const Vector3D &rhs) { return lhs += rhs; }

const Vector3D operator*(component scalar, Vector3D rhs) { return rhs *= scalar; }
const Vector3D operator*(Vector3D lhs, component scalar) { return lhs *= scalar; }

Vector3D& operator/=(Vector3D &lhs, component scalar) {
    if (scalar == 0) {
        // This should never occur. If it does, there is a flow
        // in our code, a check that isn't done, therefore we
        // print the problem and abort the program. If this happens,
        // Run gdb to see where it comes from and fix it.
        // Physicians do horrible things, but no division by zero.
        std::cout << "DIVISION By ZERO !" << std::endl;
        throw "Division by zero";
    }
    return lhs *= (1.0 / scalar);
}
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
    if(vec.isZero()) {
        // This should never occur. If it does, there is a flow
        // in our code, a check that isn't done, therefore we
        // print the problem and abort the program. If this happens,
        // Run gdb to see where it comes from and fix it.
        // Physicians do horrible things, but no division by zero.
        std::cerr << "Normalization of null vector" << std::endl;
        throw "Cannot normalize null vector";
    }
    return vec /= vec.norm();
}

component Vector3D::tripleProduct( Vector3D const& v, const Vector3D &w) const {
    return (*this) * (v ^ w);
}


// Printing


std::ostream& operator<<(std::ostream &os, const Vector3D &d) {
    os << "(" << d.x() << ", " << d.y() << ", " << d.z() << ")";
    return os;
}

// Norm


component Vector3D::norm() const { return sqrt(normSquared()); }
component Vector3D::normSquared() const { return x()*x() + y()*y() + z()*z(); }
component Vector3D::distanceTo(const Vector3D &other) const { return (*this - other).norm(); }


Vector3D Vector3D::rotate(const Vector3D &axis, double angle) const {
    Vector3D a = ~axis;  // make it unit, zero check is performed in operator~
    double c(cos(angle));
    double s(sin(angle));

    return c * (*this)
        + (1 - c) * ((*this) * a) * a
        + s * (a ^ (*this));
}

bool Vector3D::isZero() const {
    return fabs(x()) < getPrecision()
           && fabs(y()) < getPrecision()
           && fabs(z()) < getPrecision();
}
