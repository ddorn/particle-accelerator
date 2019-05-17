//
// Created by diego on 5/7/19.
//

#ifndef PARTICLEACCELERATOR_THEMES_H
#define PARTICLEACCELERATOR_THEMES_H

#include <chrono>
#include "Vector3D.h"

using namespace std::chrono;

typedef Vector3D Color;

class Theme {
protected:
    bool particleFilled;
    bool elementFilled;
    double elementTransparency;
    Color particleColor;
    Color dipoleColor;
    Color quadrupoleColor;
    Color segmentColor;
    Color bgColor;
    Color sextupoleColor;
public:
    Theme(bool particleFilled, bool elementFilled, double elementTransparency, const Color &particleColor,
          const Color &dipoleColor, const Color &quadrupoleColor, const Color &segmentColor,
          const Color &sextupoleColor, const Color &bgColor = Color())
            : particleFilled(particleFilled),
              elementFilled(elementFilled),
              elementTransparency(elementTransparency),
              particleColor(particleColor),
              dipoleColor(dipoleColor),
              quadrupoleColor(quadrupoleColor),
              segmentColor(segmentColor),
              bgColor(bgColor),
              sextupoleColor(sextupoleColor) {}

    Theme(bool particleFilled, bool elementFilled, double elementTransparency, const Color &particleColor,
          const Color &elementColor, const Color &bgColor = Color())
            : particleFilled(particleFilled),
              elementFilled(elementFilled),
              elementTransparency(elementTransparency),
              particleColor(particleColor),
              dipoleColor(elementColor),
              quadrupoleColor(elementColor),
              segmentColor(elementColor),
              bgColor(bgColor),
              sextupoleColor(elementColor) {}

    static Theme Matrix() {
        return Theme(true, false, 1, Color(1, 1, 1), Color(0, 0.23, 0));
    }

    static Theme Classix(bool dark = true) {

        Theme classix = Theme(true, true, 0.5, Color(1, 1, 1), Color(1, 0, 0), Color(1, 0.7, 0), Color(0.2, 0.6, 1),
                     Color(0.965, 0.141, 0.349));
        if (!dark) classix.bgColor = Vector3D(1, 1, 1);
        return classix;
    }

    static Theme SteamPunx() {
        return Theme(true, true, 0.7, Color(0.847, 0.596, 0.251), Color(0.173, 0.122, 0.102), Color(1, 1, 1)*0.7);
    }

    static Theme Pinx() {
        return Theme(true, true, 0.5,
                Color(1.0, 0.749, 0.827),
                Color(1.0, 0.0, 0.663),
                Color(0.984, 0.345, 0.345),
                Color(0.984, 0.624, 0.624),
                Color(0.973, 0.341, 0.835),
                Color(1.0, 0.8, 0.396));
    }

    bool isParticleFilled() const {
        return particleFilled;
    }

    bool isElementFilled() const {
        return elementFilled;
    }

    double getElementTransparency() const {
        return elementTransparency;
    }

    virtual const Color getParticleColor() const {
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

    const Color &getSextupoleColor() const {
        return sextupoleColor;
    }

    const Color &getBgColor() const {
        return bgColor;
    }

};

class Rainbox : public Theme {
public:

    /**
     * Converts aa HSV color to RGB
     * @param H hue in degres (0 to 360)
     * @param S saturation (0 to 1)
     * @param V value (0 to 1)
     * @return the RGB color with components between 0 and 1.
     */
    static const Color HSVtoRGB(int H, double S, double V) const {
        double C = S * V;
        double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
        double m = V - C;
        double Rs, Gs, Bs;

        if (H >= 0 && H < 60) {
            Rs = C;
            Gs = X;
            Bs = 0;
        } else if (H >= 60 && H < 120) {
            Rs = X;
            Gs = C;
            Bs = 0;
        } else if (H >= 120 && H < 180) {
            Rs = 0;
            Gs = C;
            Bs = X;
        } else if (H >= 180 && H < 240) {
            Rs = 0;
            Gs = X;
            Bs = C;
        } else if (H >= 240 && H < 300) {
            Rs = X;
            Gs = 0;
            Bs = C;
        } else {
            Rs = C;
            Gs = 0;
            Bs = X;
        }

        return Color(
                (Rs + m),
                (Bs + m),
                (Gs + m));
    }
    Rainbox() : Theme(true, false, 1, Color(), Color(1, 1, 1)*0.7) {}

    const Color getParticleColor() const override {
        long ms = system_clock::now().time_since_epoch().count();  // Color depends on the time
        return HSVtoRGB((ms / 30000000) % 360, 1, 1);
    }


};

#endif //PARTICLEACCELERATOR_THEMES_H
