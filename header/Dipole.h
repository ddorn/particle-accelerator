//
// Created by diego on 3/28/19.
//

#ifndef PARTICLEACCELERATOR_DIPOLE_H
#define PARTICLEACCELERATOR_DIPOLE_H

#include "CurvedElement.h"

class Dipole : public CurvedElement {
private:
    /**
     * magnetic field. Unit : tesla.
     */
    const Vector3D magneticField_;
    const Vector3D idealMagneticField(double mass, double charge, double energy) const;

public:
    /**
     * Because the elements are all in the x-y plane,
     * the dipoles can only apply a vertical magnetic field.
     * So the constructor asks a double, not a vector, to assure that.
     */
    Dipole(const Vector3D &start, const Vector3D &exit, double radius, Element *nextElement,
           double curvature, double magneticFieldIntensity) :
            CurvedElement(start, exit, radius, nextElement, curvature),
            magneticField_(magneticFieldIntensity * Vector3D::e3) {}
    /**
     * This constructor takes the mean characteristics of
     * the particles and calculates the ideal magnetic field.
     */
    Dipole(const Vector3D &start, const Vector3D &exit, double radius, Element *nextElement,
            double curvature, double mass, double charge, double energy) :
            CurvedElement(start, exit, radius, nextElement, curvature),
            magneticField_(idealMagneticField(mass, charge, energy)) {}
    const Vector3D magneticForceAt(const Vector3D &) const override { return magneticField_; }

    std::ostream &print(std::ostream &os) const override;

    void draw(Support &support) const override { support.draw(*this); }
};


#endif //PARTICLEACCELERATOR_DIPOLE_H
