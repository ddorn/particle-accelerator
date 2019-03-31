//
// Created by Gabin on 17.03.2019.
//

#include "CurvedElement.h"
#include <cmath>

Vector3D CurvedElement::centerOfCurvature() const {
    Vector3D L(exit() - entree());
    Vector3D direction(~L);
    return (entree() + exit())/2 + 1/ curvature()
    * sqrt(1 - curvature() * curvature() / 4 * L.normSquared()) * (direction ^ Vector3D::e3);
}

bool CurvedElement::collideBorder(const Vector3D &position) const {
    Vector3D X(position - centerOfCurvature());
    Vector3D u(~(X - X.z() * Vector3D::e3));
    return (X - u / fabs(curvature())).normSquared() > radius() * radius();
}

bool CurvedElement::isOut(const Vector3D& position) const {
    Vector3D e3(0,0,1);
    return(e3.tripleProduct(position, exit()) > 0);
}

double CurvedElement::curvature() const {
    return curvature_;
}

std::ostream &CurvedElement::print(std::ostream &os) const {
    Element::print(os);
    os << " - curvature : " << curvature() << std::endl
       << " - center of curvature : " << centerOfCurvature() << std::endl;
    return os;
}
