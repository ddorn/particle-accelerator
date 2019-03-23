//
// Created by Gabin on 17.03.2019.
//

#include "CurvedElement.h"
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

bool CurvedElement::isOut(const Vector3D& position) const {
    Vector3D e3(0,0,1);
    return(e3.tripleProduct(position, exit()) > 0);
}

double CurvedElement::curveture() const {
    return curveture_;
}

std::ostream &operator<<(std::ostream &os, const CurvedElement &elem) {
    os << "Curved element :" << std::endl
        << " - entree : " << elem.entree() << std::endl
        << " - exit : " << elem.exit() << std::endl
        << " - radius : " << elem.radius() << std::endl
        << " - curveture : " << elem.curveture() << std::endl
        << " - center of curveture : " << elem.centerOfCurveture() << std::endl;
    return os;
}