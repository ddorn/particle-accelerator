//
// Created by Gabin on 31.03.2019.
//

#ifndef PARTICLEACCELERATOR_QUADRUPOLE_H
#define PARTICLEACCELERATOR_QUADRUPOLE_H


#include "StraightElement.h"
#include "Element.h"

class Quadrupole : public StraightElement{
public:
    Quadrupole(const Vector3D &entree, const Vector3D &exit, double radius, double intensity,
               double longitudinalPosition)
            : StraightElement(entree, exit, radius, longitudinalPosition), intensity_(intensity) {}

    /**
     * The magnetic force concentrates the beam of particles
     */
    const Vector3D magneticForceAt(const Vector3D& position) const override;

    void draw(Support &support) const override { support.draw(*this); }

    virtual std::ostream& print(std::ostream &os) const override;

private:
    /**
     * Magnetic intensity. Unit : tesla.
     */
    double intensity_;
};

#endif //PARTICLEACCELERATOR_QUADRUPOLE_H