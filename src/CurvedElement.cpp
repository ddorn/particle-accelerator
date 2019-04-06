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

double CurvedElement::radiusCircle() const{
    return 1/curvature();
}

double CurvedElement::radialDistanceSqrd(const Vector3D &position) const{
    Vector3D X(position - centerOfCurvature());
    Vector3D dir(X.x(), X.y(), 0);
    double transversalDistance(radiusCircle() - dir.norm());
    return transversalDistance * transversalDistance + X.z() * X.z();
}

bool CurvedElement::collideBorder(const Vector3D &position) const {
    /**
     *  I don't understand what you did, and I'm not sure
     *  it's correct, so I prefer to do a simpler version.
     *  And we don't need to control if it's a the center
     *  of curvature.
     */
    /*
    Vector3D X(position - centerOfCurvature());
    Vector3D dir(X.x(), X.y(), 0);

    // A particle shouln't be on the center of curvature
    // (or the element is too fat)
    if (dir.isZero()) return false;

    return (X - ~dir / fabs(curvature())).normSquared() > radius() * radius();
     */
    return radialDistanceSqrd(position) > radius() * radius();
}

bool CurvedElement::isOut(const Vector3D& position) const {
    return Vector3D::e3.tripleProduct(position - centerOfCurvature(), exit() - centerOfCurvature()) > 0;
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
