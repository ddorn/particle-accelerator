//
// Created by Gabin on 08.03.2019.
//

#include <cmath>
#include <iostream>

#include "Particle.h"
#include "Element.h"

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
    if (dt <= 0) return;

    // Euler-Cramer integrator
    momentum_ += force_ * dt;
    position_ += speed() * LIGHT_SPEED_MS * dt;
    force_ *= 0;  // Reuse the same object instead of creating a new one;
}

void Particle::addMagneticForce(const Vector3D &b, double dt) {
    if (dt <= 0) return;

    Vector3D force = charge() * (speed() ^ (b * KG / COULOMB)); // the magnetic intensity is in tesla, we
    if (force.isZero()) return;                                 // do the conversion in GeV / c^2 / s / e

    double correction_angle = asin(dt * force.norm() /
            (2 * momentum().norm()));

    Vector3D correction(speed() ^ force);
    if (correction.isZero()) return;
    force_ += force.rotate(correction, correction_angle);
}

bool Particle::updateElement() {
    if (element_->collideBorder(position())) {
        return false;
    }
    if (element_->isOut(position())) {
        if (element_->nextElement() == nullptr) {
            return false;
        } else {
            element_ = element_->nextElement();
        }
    }
    return true;
}

double Particle::radialDistanceSqrd() const {
    return element()->radialDistanceSqrd(position());
}

double Particle::radialVelocitySqrd() const {
    return element()->radialVelocitySqrd(position(), speed());
}

std::ostream &operator<<(std::ostream &os, const Particle &partic) {
    Vector3D force(partic.charge() * (partic.speed() ^
    (partic.element()->magneticForceAt(partic.position())) * KG / COULOMB));
    double correctionAngle(asin(1e-11 * force.norm() / 2 / partic.momentum().norm()));
    os << "Particle :" << std::endl
        << " - mass : " << partic.mass() << " GeV / c²" << std::endl
        << " - charge : " << partic.charge() << " eV" << std::endl
        << " - position : " << partic.position() << std::endl
        << " - gamma : " << partic.gamma() << std::endl
        << " - momentum : " << partic.momentum() << " GeV / c" << std::endl
        << " - energy : " << partic.energy() << " GeV" << std::endl
        << " - velocity : " << partic.velocity() << " c" << std::endl
        << " - speed : " << partic.speed() << " c" << std::endl
        << " - speed in m/s " << partic.speed() * LIGHT_SPEED_MS << " m/s" << std::endl
        << " - force : " << force << std::endl
        << " - force in N : " << partic.charge() * C_PROTON_COULOMB * ((partic.speed() * LIGHT_SPEED_MS) ^ partic.element()->magneticForceAt(partic.position())) << std::endl
        << " - correction angle : " << correctionAngle << " rad" << std::endl;
    return os;
}

const Vector3D momentumFromSpeed(const Vector3D &speed, double mass) {
    return 1/sqrt(1 - speed.normSquared() / LIGHT_SPEED_SQUARED) * mass * speed;
}