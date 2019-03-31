//
// Created by Gabin on 31.03.2019.
//

#include "Quadrupole.h"

const Vector3D Quadrupole::magneticForceAt(const Vector3D & position) const{
    Vector3D e3(0,0,1);
    Vector3D X(position - entree());
    Vector3D direction(~(exit() - entree()));
    Vector3D y(X - (X * direction) * direction);
    Vector3D u(e3 ^ direction);
    return intensity_ * ((y * u) * e3 + X.z() * u);
}