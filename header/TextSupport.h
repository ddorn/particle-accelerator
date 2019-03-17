//
// Created by diego on 3/17/19.
//

#ifndef PARTICLEACCELERATOR_TEXTSUPPORT_H
#define PARTICLEACCELERATOR_TEXTSUPPORT_H

#include <iostream>
#include "Support.h"
#include "Particle.h"
#include "Element.h"
#include "Vector3D.h"

class TextSupport : public Support {
private:
    std::ostream& ostream_;

public:
    explicit TextSupport(std::ostream &ostream) : ostream_(ostream) {}

    void draw(const Particle &particle) override;
    void draw(const Element &element) override;
    void draw(const Vector3D &vector) override;
};


#endif //PARTICLEACCELERATOR_TEXTSUPPORT_H
