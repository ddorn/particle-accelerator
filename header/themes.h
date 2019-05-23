//
// Created by diego on 5/7/19.
//

#ifndef PARTICLEACCELERATOR_THEMES_H
#define PARTICLEACCELERATOR_THEMES_H

#include <chrono>
#include "Vector3D.h"

#define CLAMP01(X) X > 1 ? 1 : X < 0 ? 0 : X

using namespace std::chrono;


class Color {
private:
    double r_;
    double g_;
    double b_;
    double a_;
    double rainbowPeriod_ = 0;
public:
    /**
     * Create a color with red, green, blue and alpha between 0 and 1.
     */
    Color(double r, double g, double b, double a = 1) : r_(CLAMP01(r)), g_(CLAMP01(g)), b_(CLAMP01(b)),
                                                        a_(CLAMP01(a)) {}

    /**
     * Create a color with integer red, green and blue values between 0 and 255. Alpha is between 0 and 1.
     */
    Color(int r, int g, int b, double a = 1) : Color(r / 255.0, g / 255.0, b / 255.0, a) {}

    /**
     * Create a color from the HSV space.
     * @param hue Angle between 0 and 360
     * @param saturation Saturation between 0 and 1
     * @param value Value between 0 and 1
     * @param a Alpha between 0 and 1
     */
    Color(int hue, double saturation, double value, double a = 1) : a_(CLAMP01(a)) {
        double C = saturation * value;
        double X = C * (1 - abs(fmod(hue / 60.0, 2) - 1));
        double m = value - C;
        double Rs, Gs, Bs;

        if (hue >= 0 && hue < 60) {
            Rs = C;
            Gs = X;
            Bs = 0;
        } else if (hue >= 60 && hue < 120) {
            Rs = X;
            Gs = C;
            Bs = 0;
        } else if (hue >= 120 && hue < 180) {
            Rs = 0;
            Gs = C;
            Bs = X;
        } else if (hue >= 180 && hue < 240) {
            Rs = 0;
            Gs = X;
            Bs = C;
        } else if (hue >= 240 && hue < 300) {
            Rs = X;
            Gs = 0;
            Bs = C;
        } else {
            Rs = C;
            Gs = 0;
            Bs = X;
        }

        r_ = Rs + m;
        g_ = Gs + m;
        b_ = Bs + m;
    }

    Color() : Color(1.0, 1.0, 1.0) {}

    /**
     * Rainbow changing color
     * @param rainbowPeriod revolution period  in seconds
     * @param a Alpha between 0 and 1
     */
    Color(double rainbowPeriod, double a = 1) : a_(a), rainbowPeriod_(rainbowPeriod < 0 ? 1 : rainbowPeriod) {}

    double r() const { return rainbowPeriod_ == 0 ? r_ : rainbowColor().r(); }
    double g() const { return rainbowPeriod_ == 0 ? g_ : rainbowColor().g(); }
    double b() const { return rainbowPeriod_ == 0 ? b_ : rainbowColor().b(); }
    double a() const { return a_; }

    void setR(double r) { r_ = CLAMP01(r); }
    void setG(double g) { g_ = CLAMP01(g); }
    void setB(double b) { b_ = CLAMP01(b); }
    void setA(double a) { a_ = CLAMP01(a); }

private:
    const Color rainbowColor() const {
        if (rainbowPeriod_ <= 0) return *this;
        double t(system_clock::now().time_since_epoch().count());
        t /=  rainbowPeriod_ * 1e9;
        t *= 360;
        return Color(int(fmod(t, 360)), 1.0, 1.0);
    }
};

class Theme {
protected:
    bool particleFilled_;
    bool elementFilled_;
    Color particleColor_;
    Color dipoleColor_;
    Color quadrupoleColor_;
    Color segmentColor_;
    Color bgColor_;
    Color sextupoleColor_;
public:
    Theme(bool particleFilled, bool elementFilled, double elementTransparency, const Color &particleColor,
          const Color &dipoleColor, const Color &quadrupoleColor, const Color &segmentColor,
          const Color &sextupoleColor, const Color &bgColor = Color(0, 0, 0))
            : particleFilled_(particleFilled),
              elementFilled_(elementFilled),
              particleColor_(particleColor),
              dipoleColor_(dipoleColor),
              quadrupoleColor_(quadrupoleColor),
              segmentColor_(segmentColor),
              bgColor_(bgColor),
              sextupoleColor_(sextupoleColor) {
        dipoleColor_.setA(elementTransparency);
        quadrupoleColor_.setA(elementTransparency);
        segmentColor_.setA(elementTransparency);
        sextupoleColor_.setA(elementTransparency);
    }

    Theme(bool particleFilled, bool elementFilled, double elementTransparency, const Color &particleColor,
          const Color &elementColor, const Color &bgColor = Color(0, 0, 0))
            : Theme(particleFilled, elementFilled, elementTransparency, particleColor, elementColor, elementColor,
                    elementColor, elementColor, bgColor) {}

    static Theme Matrix() {
        return Theme(true, false, 1, Color(), Color(0., 0.23, 0.));
    }
    static Theme Classix(bool dark = true) {

        Theme classix = Theme(true, true, 0.5,
                              Color(),
                              Color(1.0, 0.0, 0.0),
                              Color(1.0, 0.7, 0.0),
                              Color(0.2, 0.6, 1.0),
                              Color(0.965, 0.141, 0.349));
        if (!dark) classix.bgColor_ = Color();
        return classix;
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
    static Theme EPFL() {
        return Theme(true, true, 0.7,
                Color(0,0,0,0),
                Color(1., 0., 0.),
                Color(0,0,0));
    }
    static Theme RouteArcEnCiel() {
        return Theme(true, true, 0.7, Color(0, 1., 1.), Color(5));
    };
    static Theme CurseOfDarkRainbow() {
        return Theme(true, true, 0.7, Color(1), Color(3), Color(5));
    }
    static Theme Zloopix() {
        return Theme(true, true, 0, Color(1., 1., 1., 0), Color(1.0, 1.0, 1.0));
    }

    bool isParticleFilled() const { return particleFilled_; }
    bool isElementFilled() const { return elementFilled_; }

    const Color particleColor() const { return particleColor_; }
    const Color &dipoleColor() const { return dipoleColor_; }
    const Color &quadrupoleColor() const { return quadrupoleColor_; }
    const Color &segmentColor() const { return segmentColor_; }
    const Color &sextupoleColor() const { return sextupoleColor_; }
    const Color &bgColor() const { return bgColor_; }

};

#endif //PARTICLEACCELERATOR_THEMES_H
