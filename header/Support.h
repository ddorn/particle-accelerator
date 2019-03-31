//
// Created by diego on 3/17/19.
//

#ifndef PARTICLEACCELERATOR_SUPPORT_H
#define PARTICLEACCELERATOR_SUPPORT_H

// We need forward definitions of classes, because
// those classes need to include Support in their
// headers so one has to be defined before the other.
// And we choosed Support as it's a very light class
class Vector3D;
class Particle;
class Element;
class Dipole;
class Accelerator;
class Quadrupole;
class CurvedElement;
class StraightElement;


class Content;

class Support {
public:
    virtual ~Support() = default;;
    virtual void draw(const Accelerator&) = 0;
    virtual void draw(const CurvedElement&) = 0;
    virtual void draw(const Dipole&) = 0;
    virtual void draw(const Element&) = 0;
    virtual void draw(const Particle&) = 0;
    virtual void draw(const Quadrupole&) = 0;
    virtual void draw(const StraightElement&) = 0;
    virtual void draw(const Vector3D&) = 0;

};
#endif //PARTICLEACCELERATOR_SUPPORT_H
