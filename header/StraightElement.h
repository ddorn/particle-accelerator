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
protected:
    const Vector3D direction;  // We store it as it shouldn't change and it simplifies expressions
    const Vector3D radial_direction;  // We store it as it shouldn't change and it simplifies expressions
public:
    StraightElement(const Vector3D &start, const Vector3D &exit, double radius, double longitudinalPosition)
            : Element(start, exit, radius, longitudinalPosition),
            direction(~(exit - start)),
            radial_direction(Vector3D::e3 ^ direction) {}

    // TODO: remove both
    double radialDistanceSqrd(Vector3D pos) const override;
    double radialVelocitySqrd(const Vector3D &position, const Vector3D &speed) const override;

    const RadialVec3D radialPosition(Vector3D pos) const override;
    const RadialVec3D radialSpeed(const Vector3D &absolutePosition, const Vector3D &absoluteSpeed) const override;
    const Vector3D absolutePosition(const RadialVec3D &radialPos) const override;
    const Vector3D absoluteSpeed(const RadialVec3D &relativePosition, const RadialVec3D &relativeSpeed) const override;
	
	double length() const override;
    void draw(Support &support) const override { support.draw(*this); }
};


#endif //PARTICLEACCELERATOR_STRAIGHTELEMENT_H
