//
// Created by diego on 3/17/19.
//

#ifndef PARTICLEACCELERATOR_TEXTSUPPORT_H
#define PARTICLEACCELERATOR_TEXTSUPPORT_H

#include <iostream>
#include "all.h"

class TextSupport : public Support {
private:
    std::ostream& ostream_;

public:
    explicit TextSupport(std::ostream &ostream) : ostream_(ostream) {}

    void draw(const Particle &particle) override;
    void draw(const Element &element) override;
    void draw(const Vector3D &d) override;
    void draw(const Dipole &dipole) override;
    void draw(const Accelerator &accelerator) override;
    void draw(const CurvedElement &element) override;
    void draw(const Quadrupole &quadrupole) override;
    void draw(const StraightElement &element) override;

    void draw(const Segment &segment) override;
};


#endif //PARTICLEACCELERATOR_TEXTSUPPORT_H
