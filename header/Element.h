//
// Created by Gabin on 17.03.2019.
//

#ifndef PARTICLEACCELERATOR_ELEMENT_H
#define PARTICLEACCELERATOR_ELEMENT_H


#include "Vector3D.h"
#include "Particle.h"



class Element{
private:
    Vector3D entree_;
    Vector3D exit_;
    Vector3D radius_;
    Element* nextElement_;
public:
    Element(const Vector3D &entree, const Vector3D &exit, const Vector3D &radius, Element *nextElement) : entree_(
            entree), exit_(exit), radius_(radius), nextElement_(nextElement) {}

    bool collideBorder(const Vector3D& position) const;
    bool isOut(const Vector3D& position) const;

    const Vector3D &entree() const;

    const Vector3D &exit() const;

    const Vector3D &radius() const;

    Element *nextElement() const;


};

std::ostream& operator<<(std::ostream& os, const Element &element);

#endif //PARTICLEACCELERATOR_ELEMENT_H