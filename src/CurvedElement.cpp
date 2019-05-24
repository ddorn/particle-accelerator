//
// Created by Gabin on 17.03.2019.
//

#include "CurvedElement.h"
#include <cmath>


const Vector3D CurvedElement::calculateCenterOfCurvature() const {
    Vector3D L(exit() - start());
    Vector3D direction(~L);
    return (start() + exit()) / 2.0
           + 1.0
             / curvature()
             * sqrt(1.0 - curvature() * curvature() / 4.0 * L.normSquared())
             * (direction ^ Vector3D::e3);
}

double CurvedElement::radialDistanceSqrd(Vector3D pos) const{
    Vector3D X(pos - centerOfCurvature());
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


bool CurvedElement::isOut(Vector3D pos, bool clockwise) const {
//    return Vector3D::e3.tripleProduct(pos - centerOfCurvature(), exit() - centerOfCurvature()) > 0;
    if (clockwise) return Vector3D::e3.tripleProduct(pos, exit()) > 0;
    else return Vector3D::e3.tripleProduct(pos, start()) < 0;
}


std::ostream &CurvedElement::print(std::ostream &os) const {
    Element::print(os);
    os << " - curvature : " << curvature() << std::endl
       << " - center of curvature : " << centerOfCurvature() << std::endl;
    return os;
}

const RadialVec3D CurvedElement::radialPosition(Vector3D pos) const {
    Vector3D X(pos - centerOfCurvature());
    X -= X.z() * Vector3D::e3;
    if (X.isZero()) return RadialVec3D(0, 0, pos.z());

    Vector3D dir(~X);
    Vector3D dirEntree(~(start() - centerOfCurvature()));
    // For S, we need to calculate the angle between the dir and the start,
    // but because we suppose no Element makes more than a half turn, it is
    // just the acos of the projection of dir over the start
    double angle(acos(dir * dirEntree));
    return RadialVec3D(X.norm() - radiusCircle(), radiusCircle() * angle, pos.z());
}

const RadialVec3D CurvedElement::radialSpeed(const Vector3D &absolutePosition, const Vector3D &absoluteSpeed) const {
    Vector3D planePosition(absolutePosition.x(), absolutePosition.y(), 0);
    Vector3D planeSpeed(absoluteSpeed.x(), absoluteSpeed.y(), 0);
    Vector3D dir(~(planePosition - centerOfCurvature()));
    double r(planeSpeed * dir);
    double s((planeSpeed - r * dir).norm());
//    std::cout << absoluteSpeed << absolutePosition << Vector3D(r, s, absoluteSpeed.z()) << std::endl;
    return RadialVec3D(r, s, absoluteSpeed.z());
}

const Vector3D CurvedElement::absolutePosition(const RadialVec3D &radialPos) const {
    const Vector3D cc(centerOfCurvature());
    Vector3D dir((start() - cc).rotate(Vector3D::e3, -radialPos.s() / radiusCircle()));
    dir *= 1 + radialPos.r() / radiusCircle();
    dir += cc;
    return Vector3D(dir.x(), dir.y(), radialPos.z());
}

const Vector3D CurvedElement::absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const {
    const Vector3D cc(centerOfCurvature());
    Vector3D dir(~(start() - cc).rotate(Vector3D::e3, -relativePosition.s() / radiusCircle()));

    Vector3D q = dir.rotate(Vector3D::e3, relativeSpeed.s() / radiusCircle());
    return dir * relativeSpeed.r()
        + (dir ^ Vector3D::e3) * relativeSpeed.s()
        + Vector3D::e3 * relativeSpeed.z();
}

double CurvedElement::angle() const {
	Vector3D center(centerOfCurvature());
	Vector3D x(~(start() - center));
	Vector3D y(~(exit() - center));
	return std::acos(x*y);
}

