//
// Created by diego on 5/7/19.
//

#ifndef PARTICLEACCELERATOR_THEMES_H
#define PARTICLEACCELERATOR_THEMES_H

#include "Vector3D.h"

typedef Vector3D Color;

class Theme {
private:
    bool particleFilled;
    bool elementFilled;
    double elementTransparency;
    Color particleColor;
    Color dipoleColor;
    Color quadrupoleColor;
    Color segmentColor;
public:
    Theme(bool particleFilled, bool elementFilled, double elementTransparency, const Color &particleColor,
          const Color &dipoleColor, const Color &quadrupoleColor, const Color &segmentColor) : particleFilled(particleFilled),
                                                                                               elementFilled(elementFilled),
                                                                                               elementTransparency(elementTransparency),
                                                                                               particleColor(particleColor),
                                                                                               dipoleColor(dipoleColor),
                                                                                               quadrupoleColor(quadrupoleColor),
                                                                                               segmentColor(segmentColor)
                                                                                               {}

    bool isParticleFilled() const {
        return particleFilled;
    }

    bool isElementFilled() const {
        return elementFilled;
    }

    double getElementTransparency() const {
        return elementTransparency;
    }

    virtual const Color &getParticleColor() const {
        return particleColor;
    }

    const Color &getDipoleColor() const {
        return dipoleColor;
    }

    const Color &getQuadrupoleColor() const {
        return quadrupoleColor;
    }

    const Color &getSegmentColor() const {
        return segmentColor;
    }

};


class Matrix : public Theme {
public:
    Matrix() : Theme(true, false, 1, Color(1, 1, 1), Color(0, 0.23, 0), Color(0, 0.23, 0), Color(0, 0.23, 0)) {}
};

class Classix : public Theme {
public:
    Classix() : Theme(true, true, 0.5, Color(1, 1, 1), Color(1, 0, 0), Color(1, 0.7, 0), Color(0.2, 0.6, 1)) {}
};

#endif //PARTICLEACCELERATOR_THEMES_H
