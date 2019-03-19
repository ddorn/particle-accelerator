//
// Created by diego on 3/17/19.
//

#ifndef PARTICLEACCELERATOR_SUPPORT_H
#define PARTICLEACCELERATOR_SUPPORT_H

#include "Particle.h"
#include "Element.h"
#include "Vector3D.h"


class Content;

class Support {
public:
    virtual ~Support() = default;;
    virtual void draw(const Particle&) = 0;
    virtual void draw(const Element&) = 0;
};
#endif //PARTICLEACCELERATOR_SUPPORT_H
