//
// Created by diego on 3/28/19.
//

#ifndef PARTICLEACCELERATOR_DIPOLE_H
#define PARTICLEACCELERATOR_DIPOLE_H

#include "CurvedElement.h"

class Dipole : public CurvedElement {
private:
    Vector3D magneticField_;

public:
    /**
     * Because the elements are all in the x-y plane,
     * the dipoles can only apply a vertical magnetic field.
     * So the constructor asks a double, not a vector, to assure that.
     */
    Dipole(const Vector3D &entree, const Vector3D &exit, double radius, Element *nextElement,
           double curvature, double magneticFieldIntensity) :
            CurvedElement(entree, exit, radius, nextElement, curvature),
            magneticField_(Vector3D(0, 0, magneticFieldIntensity)) {}

    const Vector3D magneticForceAt(const Vector3D &) const override {
        return magneticField_;
    }

    std::ostream &print(std::ostream &os) const override {
        CurvedElement::print(os);
        os << " - Magnetic field : " << magneticField_ << std::endl;
        return os;
    }

    void draw(Support &support) override { support.draw(*this); }
};


#endif //PARTICLEACCELERATOR_DIPOLE_H
