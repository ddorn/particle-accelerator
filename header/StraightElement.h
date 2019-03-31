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
    void draw(Support &support) override { support.draw(*this); }
};


#endif //PARTICLEACCELERATOR_STRAIGHTELEMENT_H