//
// Created by Gabin on 17.03.2019.
//

#include "CurvedElement.h"
#include <cmath>
#include <CurvedElement.h>


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

double CurvedElement::radialVelocitySqrd(const Vector3D &position, const Vector3D &speed) const {
    Vector3D X(position - centerOfCurvature());
    if(X.x() == 0 and X.y() == 0){
        return 0;
    }
    Vector3D dir(~Vector3D(X.x(), X.y(),0));
    double transversalVelocity(speed * dir);
    return transversalVelocity * transversalVelocity + speed.z() * speed.z();
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

const RadialVec3D CurvedElement::radialPosition(const Vector3D &pos) const {
    Vector3D X(pos - centerOfCurvature());
    X -= X.z() * Vector3D::e3;
    if (X.isZero()) return RadialVec3D(0, 0, pos.z());

    Vector3D dir(~X);
    Vector3D dirEntree(~(entree() - centerOfCurvature()));
    // For S, we need to calculate the angle between the dir and the entree,
    // but because we suppose no Element makes more than a half turn, it is
    // just the acos of the projection of dir over the entree
    double angle(acos(dir * dirEntree));
    return RadialVec3D(pos * dir, radiusCircle() * angle, pos.z());
}

const RadialVec3D CurvedElement::radialSpeed(const Vector3D &absolutePosition, const Vector3D &absoluteSpeed) const {
    return RadialVec3D(0, 0, 0);
}

const Vector3D CurvedElement::absolutePosition(const RadialVec3D &radialPos) const {
    return Vector3D();
}

const Vector3D
CurvedElement::absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const {
    return Vector3D();
}
