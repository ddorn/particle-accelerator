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
public:
    CurvedElement(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement,
                  double curvature) : Element(entree, exit, radius, nextElement), curvature_(curvature) {}

    Vector3D centerOfCurvature() const;
    bool collideBorder(const Vector3D &position) const override;
    bool isOut(const Vector3D &position) const override;

    double curvature() const;

    std::ostream &print(std::ostream &os) const override;
    void draw(Support &support) override { support.draw(*this); }

};

#endif //PARTICLEACCELERATOR_CURVEDELEMENT_H
