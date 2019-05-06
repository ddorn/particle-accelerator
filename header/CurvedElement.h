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
    /**
     * Radius of the circle that the CurvedElement follows.
     */
    double radiusCircle() const;
public:
    CurvedElement(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement,
                  double curvature) : Element(entree, exit, radius, nextElement), curvature_(curvature) {}

    Vector3D centerOfCurvature() const;
    bool collideBorder(const Vector3D &position) const override;
    bool isOut(Vector3D pos) const override;

    // TODO: remove both
    double radialDistanceSqrd(Vector3D pos) const override;
    double radialVelocitySqrd(const Vector3D &position, const Vector3D &speed) const override;

    const RadialVec3D radialPosition(Vector3D absolutePosition) const override;
    const RadialVec3D radialSpeed(const Vector3D &absolutePosition, const Vector3D &absoluteSpeed) const override;
    const Vector3D absolutePosition(const RadialVec3D &radialPos) const override;
    const Vector3D absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const override;

    double curvature() const;
    double angle() const;
    double length() const override;

    std::ostream &print(std::ostream &os) const override;
    void draw(Support &support) const override { support.draw(*this); }

};

#endif //PARTICLEACCELERATOR_CURVEDELEMENT_H
