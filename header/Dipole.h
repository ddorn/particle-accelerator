//
// Created by diego on 3/28/19.
//

#ifndef PARTICLEACCELERATOR_DIPOLE_H
#define PARTICLEACCELERATOR_DIPOLE_H

#include "CurvedElement.h"

class Dipole : public CurvedElement{
private:
    Vector3D magneticField_;

public:
    Dipole(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement,
                  double curvature, const Vector3D &magneticField) :
                  CurvedElement(entree, exit, radius, nextElement, curvature),
                  magneticField_(magneticField)
                  {}

    const Vector3D magneticForceAt(const Vector3D &) const override {
        return magneticField_;
    }
};


#endif //PARTICLEACCELERATOR_DIPOLE_H
