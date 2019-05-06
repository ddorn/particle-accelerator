//
// Created by Gabin on 31.03.2019.
//

#include "Quadrupole.h"

const Vector3D Quadrupole::magneticForceAt(const Vector3D & position) const{
    Vector3D X(position - start());
    Vector3D direction(~(exit() - start()));
    Vector3D y(X - (X * direction) * direction);
    Vector3D u(Vector3D::e3 ^ direction);
    return intensity_ * ((y * u) * Vector3D::e3 + X.z() * u);
}