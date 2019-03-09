//
// Created by Gabin on 08.03.2019.
//

#ifndef PARTICLE_ACCELERATOR_PARTICLE_H
#define PARTICLE_ACCELERATOR_PARTICLE_H


#include "Vector3D.h"
#include "constants.h"

/**
 * --- Units ---
 * mass : GeV / c²
 * electric charge : e
 * energy : GeV
 * speed : c
 * momentum : GeV / c
 * (it's a first draft, we will see later if it's a good choice)
 */


class Particle {
public:
    Particle(double mass, double elecCharge, const Vector3D &position, const Vector3D &momentum) : mass(mass),
                                                                                                elecCharge(elecCharge),
                                                                                                position(position),
                                                                                                speed(speedFromMomentum(momentum))
                                                                                                {}



    double getElecCharge() const { return elecCharge;}

    void setElecCharge(double elecCharge) {
        elecCharge = elecCharge;
    }

    double getMass() const { return mass;}

    void setMass(double mass) {
        Particle::mass = mass;
    }

    const Vector3D &getPosition() const {return position;}

    const Vector3D &getSpeed() const {return speed;}

    void setSpeed(const Vector3D &speed) {
        Particle::speed = speed;
    }

    void setPosition(const Vector3D &position) {
        Particle::position = position;
    }


    double energy() const;
    double gamma() const;
    const Vector3D momentum() const; // These are methods for now, but it can change if we see that it's more efficient to have attributes



private:
    const Vector3D speedFromMomentum(const Vector3D &momentum); // Use to initiate a particle with a momentum
    double mass;
    double elecCharge;
    Vector3D position;
    Vector3D speed;

};

std::ostream& operator<<(std::ostream &os, const Particle &partic);

#endif //PARTICLE_ACCELERATOR_PARTICLE_H
