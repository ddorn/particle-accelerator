//
// Created by Gabin on 08.03.2019.
//

#ifndef PARTICLE_ACCELERATOR_PARTICLE_H
#define PARTICLE_ACCELERATOR_PARTICLE_H

#include <cmath>

#include "Vector3D.h"
#include "constants.h"

/**
 * --- Units ---
 * length : c * s
 * mass : GeV / c²
 * electric charge : e
 * energy : GeV
 * speed : c
 * momentum : GeV / c
 * (it's a first draft, we will see later if it's a good choice)
 */


class Particle {

private:
    double mass_;
    double charge_;
    Vector3D position_;
    Vector3D momentum_;
    Vector3D force_;

public:
    Particle(double mass, double charge, const Vector3D &position, const Vector3D &momentum) : mass_(mass),
                                                                                                charge_(charge),
                                                                                                position_(position),
                                                                                                momentum_(momentum)
                                                                                                {}

    double charge() const { return charge_; }
    void setCharge(double charge) { charge_ = charge; }

    double mass() const { return mass_; }
    void setMass(double mass) { mass_ = mass; }

    const Vector3D &momentum() const { return momentum_; }
    void setMomentum(const Vector3D &momentum) { momentum_ = momentum; }

    const Vector3D &position() const { return position_; }
    void setPosition(const Vector3D &position) { position_ = position; }

    const Vector3D speed() const;
    double velocity() const { return sqrt(velocitySquared()); }
    double velocitySquared() const;

    void applyMagneticForce( const Vector3D &force, double dt);
    void evolve(double dt);

    double energy() const;
    double gamma() const;
};

std::ostream& operator<<(std::ostream &os, const Particle &partic);

#endif //PARTICLE_ACCELERATOR_PARTICLE_H
