//
// Created by diego on 5/8/19.
//

#ifndef PARTICLEACCELERATOR_SEXTUPOLE_H
#define PARTICLEACCELERATOR_SEXTUPOLE_H

#include "StraightElement.h"

class Sextupole : public StraightElement {
private:
    double intensity_;
public:
    Sextupole(const Vector3D &start, const Vector3D &exit, double radius, double intensity,
              double longitudinalPosition) :
            StraightElement(start, exit, radius, longitudinalPosition), intensity_(intensity) {}

    const Vector3D magneticForceAt(const Vector3D &position) const override;
    void draw(Support &support) const override { support.draw(*this); }

};


#endif //PARTICLEACCELERATOR_SEXTUPOLE_H
