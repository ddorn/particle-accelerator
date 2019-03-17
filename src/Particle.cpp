//
// Created by Gabin on 08.03.2019.
//

#include <cmath>
#include <iostream>
#include "../header/Particle.h"

using namespace constants;

double Particle::gamma() const {
    return 1.0 / sqrt(1.0 - velocitySquared() / LIGHT_SPEED_SQUARED);
}
double Particle::energy() const{
    return gamma() * mass() * LIGHT_SPEED_SQUARED;
}
double Particle::velocitySquared() const {
    double momentum_squared = momentum().normSquared();
    return momentum_squared / (mass() * mass() + momentum_squared / LIGHT_SPEED_SQUARED);
}

const Vector3D Particle::speed() const {
    return LIGHT_SPEED / sqrt(mass() * mass() + momentum().normSquared()) * momentum();
}

void Particle::evolve(double dt) {
    momentum_ += force_ * dt;
    position_ += speed() * dt;
    force_ *= 0;  // Reuse the same object instead of creating a new one;
}

void Particle::addMagneticForce(const Vector3D &b, double dt) {
    if (dt <= 0) return;

    Vector3D force = charge() * (speed() ^ b);
//    std::cout << force << std::endl;
    double correction_angle = asin(dt * force.norm() /
            (2 * momentum().norm()));
//    std::cout << correction_angle << std::endl;
    force_ += force.rotate(speed() ^ force, correction_angle);
}

std::ostream &operator<<(std::ostream &os, const Particle &partic) {
    os << "Particle :" << std::endl
        << " - mass : " << partic.mass() << " GeV / c²" << std::endl
        << " - charge : " << partic.charge() << " eV" << std::endl
        << " - position : " << partic.position() << std::endl
        << " - gamma : " << partic.gamma() << std::endl
        << " - momentum : " << partic.momentum() << " GeV / c" << std::endl
        << " - energy : " << partic.energy() << " GeV" << std::endl
        << " - velocity : " << partic.velocity() << " c" << std::endl
        << " - speed : " << partic.speed() << " c" << std::endl;
    return os;
}
