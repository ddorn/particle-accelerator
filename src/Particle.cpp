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
double Particle::energy() const {
    return gamma() * mass();
}
double Particle::velocitySquared() const {
    return speed().normSquared();
}

void Particle::evolve(double dt) {
    if (dt <= 0) return;

    // Euler-Cramer integrator
    momentum_ += force_ * dt;
    speed_ += force_ * dt / gamma() / massSI();
    position_ += speed() * dt;
    lastForce_ = force_;
    force_ *= 0;  // Reuse the same object instead of creating a new one;
}

void Particle::addMagneticForce(const Vector3D &b, double dt) {
    if (dt <= 0) return;

    Vector3D force = charge() * (speed() ^ b);
    if (force.isZero()) return;

    correction_angle_ = asin(dt * force.norm() /
                             (2 * momentum().norm()));

    Vector3D correction(speed() ^ force);
    if (correction.isZero()) return;
    force_ += force.rotate(correction, correction_angle_);
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
    os << "Particle :" << std::endl
        << " - mass : " << partic.mass() << " GeV / c²" << std::endl
        << " - charge : " << partic.charge() << " C" << std::endl
        << " - position : " << partic.position() << std::endl
        << " - gamma : " << partic.gamma() << std::endl
        << " - energy : " << partic.energy() << " GeV" << std::endl
        << " - speed : " << partic.speed() << " m/s" << std::endl
        << " - corrected force : " << partic.lastForce() << std::endl
        << " - correction angle : " << partic.correctionAngle() << " rad" << std::endl;
    return os;
}

const Vector3D momentumFromSpeed(const Vector3D &speed, double mass) {
    return 1.0 / sqrt(1 - speed.normSquared() / LIGHT_SPEED_SQUARED) * mass / KG * speed;
}

const Vector3D Particle::speedFromMomentum() const {
    return momentum() / sqrt(massSI() * massSI() + (momentum() * momentum() / LIGHT_SPEED_SQUARED));
}