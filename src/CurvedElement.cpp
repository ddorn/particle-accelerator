//
// Created by Gabin on 17.03.2019.
//

#include "../header/CurvedElement.h"
#include <cmath>

Vector3D CurvedElement::centerOfCurveture() const {
    Vector3D L(exit() - entree());
    Vector3D direction(~L);
    return (entree() + exit())/2 + 1/curveture()
    * sqrt(1 - curveture() * curveture() / 4 * L.normSquared()) * (direction ^ Vector3D::e3);
}

bool CurvedElement::collideBorder(const Vector3D &position) const {
    Vector3D X(position - centerOfCurveture());
    Vector3D u(~(X - X.z() * Vector3D::e3));
    return (X - u / fabs(curveture())).normSquared() > radius() * radius();
}


double CurvedElement::curveture() const {
    return curveture_;
}
