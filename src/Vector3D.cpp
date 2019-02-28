//
// Created by diego on 2/28/19.
//

#include <cmath>
#include "../header/Vector3D.h"


component Vector3D::norm() const {
    return sqrt(normSquared());
}

component Vector3D::normSquared() const {
    return x()*x() + y()*y() + z()*z();
}

bool Vector3D::operator==(const Vector3D &rhs) const {
    return x_ == rhs.x_ &&
           y_ == rhs.y_ &&
           z_ == rhs.z_;
}

bool Vector3D::operator!=(const Vector3D &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Vector3D &d) {
    os << "Vector3D(" << d.x() << ", " << d.y() << ", " << d.z() << ")";
    return os;
}

Vector3D Vector3D::operator+(const Vector3D &rhs) const {
    return Vector3D(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());

}



