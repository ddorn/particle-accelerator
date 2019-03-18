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
    double curveture_;
public:
    CurvedElement(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement,
                  double curveture) : Element(entree, exit, radius, nextElement), curveture_(curveture) {}

    Vector3D centerOfCurveture() const;
    bool collideBorder(const Vector3D &position) const;
    bool isOut(const Vector3D &position) const;

    double curveture() const;


};
std::ostream &operator<<(std::ostream &os, const CurvedElement &elem);

#endif //PARTICLEACCELERATOR_CURVEDELEMENT_H
