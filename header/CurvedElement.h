//
// Created by Gabin on 17.03.2019.
//

#ifndef PARTICLEACCELERATOR_CURVEDELEMENT_H
#define PARTICLEACCELERATOR_CURVEDELEMENT_H

#include "Element.h"
#include "Vector3D.h"
#include "Particle.h"

class CurvedElement : public Element
{
private:
    double curvature_;
    const Vector3D centerOfCurvature_;
    /**
     * Radius of the circle that the CurvedElement follows.
     */
    double radiusCircle() const { return 1.0 / curvature(); }
    const Vector3D calculateCenterOfCurvature() const;

public:
    CurvedElement(const Vector3D &entree, const Vector3D &exit, double radius, double curvature,
                  double longitudinalPosition) :
            Element(entree, exit, radius, longitudinalPosition),
                  curvature_(curvature),
                  centerOfCurvature_(calculateCenterOfCurvature())
                  {}

    double angle() const;
    double length() const override { return angle() * radiusCircle(); }
    double curvature() const { return curvature_; }
    const Vector3D &centerOfCurvature() const { return centerOfCurvature_; }

    // TODO: remove both
    double radialDistanceSqrd(Vector3D pos) const override;
    double radialVelocitySqrd(const Vector3D &position, const Vector3D &speed) const override;

    const RadialVec3D radialPosition(Vector3D absolutePosition) const override;
    const RadialVec3D radialSpeed(const Vector3D &absolutePosition, const Vector3D &absoluteSpeed) const override;
    const Vector3D absolutePosition(const RadialVec3D &radialPos) const override;
    const Vector3D absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const override;

    std::ostream &print(std::ostream &os) const override;
    void draw(Support &support) const override { support.draw(*this); }

};

#endif //PARTICLEACCELERATOR_CURVEDELEMENT_H
