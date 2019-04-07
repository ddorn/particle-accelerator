//
// Created by Gabin on 17.03.2019.
//

#ifndef PARTICLEACCELERATOR_STRAIGHTELEMENT_H
#define PARTICLEACCELERATOR_STRAIGHTELEMENT_H
#include "Element.h"
#include "Vector3D.h"
#include "Particle.h"

class StraightElement : public Element
{
public:
    StraightElement(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement)
            : Element(entree, exit, radius, nextElement) {}

    bool collideBorder(const Vector3D& position) const override;
    bool isOut(const Vector3D& position) const override;

    double radialDistanceSqrd(const Vector3D &position) const override;
    double radialVelocitySqrd(const Vector3D &position, const Vector3D &speed) const override;

    const RadialVec3D radialPosition(const Vector3D &absolutePosition) const override;
    const RadialVec3D radialSpeed(const Vector3D &absolutePosition, const Vector3D &absoluteSpeed) const override;
    const Vector3D absolutePosition(const RadialVec3D &radialPos) const override;
    const Vector3D absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const override;

    void draw(Support &support) const override { support.draw(*this); }
};


#endif //PARTICLEACCELERATOR_STRAIGHTELEMENT_H