//
// Created by diego on 5/6/19.
//

#include "Particle.h"
#include "constants.h"

using namespace constants;
using namespace std;

double Particle::velocityFromEnergy(double energy, double mass) const {
    return LIGHT_SPEED * sqrt(1 - mass * mass / (energy * energy));
}

void Particle::addMagneticForce(const Vector3D &b, double dt) {
    if (dt <= 0) return;

    Vector3D force(charge() * speed() ^ b);

    if (force.isZero()) return;

    double angle(asin(dt * force.norm()
                      / (2 * gamma() * massSI() * velocity())));

    const Vector3D axis(speed() ^ force);
    if (axis.isZero()) {
        cerr << "Axis was zero but this shouldn't happen" << endl;
        return;
    }

    force_ += force.rotate(axis, angle);

}

void Particle::addElectricForce(const Vector3D& e){
    force_ += charge() * e;
}

bool Particle::evolve(double dt) {
    speed_ += dt * force_ / (gamma() * massSI());
    position_ += dt * speed_;
    updateCachedAttributes();  // Position, speed and force changed
    force_ *= 0;  // We reuse the same object

    updateElement();
    return !isAlive();
}

bool Particle::updateElement() {
    if (element()->collideBorder(position())) {
        isAlive_ = false;
        return false;
    }

    if (element()->isOut(position(), clockwise())) {
        if (element()->nextElement() == nullptr) {
            isAlive_ = false;
            return false;
        }

        // update to the correct next element
        element_ = clockwise() ? element()->nextElement()
                               : element()->previousElement();
        // Count a turn if again in the element it started
        if (element_ == spawn_) turns_ += 1;
    }

    return true;
}

const Vector3D Particle::magneticFieldAt(const Vector3D &pos) const {
    return 1.0 / constants::LIGHT_SPEED_SQUARED * (speed() ^ electricFieldAt(pos));
}

const Vector3D Particle::electricFieldAt(const Vector3D &pos) const {
    Vector3D d(pos - position());
    double dist(d.norm());
    return charge()/(4 * M_PI * constants::VACUUM_PERMITTIVITY * dist * dist * dist) * d;
}

void Particle::particleInteraction(Particle& p, double dt){
    if(p.position() == position()){
        // If they are at the same position, they collided and they DIE.
        isAlive_ = false;
        p.isAlive_ = false;
        return;
    }
    addMagneticForce(p.magneticFieldAt(position()), dt);
    addElectricForce(p.electricFieldAt(position()));
    p.addMagneticForce(magneticFieldAt(p.position()), dt);
    p.addElectricForce(electricFieldAt(p.position()));
}

void Particle::updateCachedAttributes() {
    radialPosition_ = element_->radialPosition(position_);
    radialSpeed_ = element_->radialSpeed(position_, speed_);
    lastForce_ = force_;
    gamma_ = 1.0 / sqrt(1.0 - velocitySquared() / constants::LIGHT_SPEED_SQUARED);
}

std::ostream& operator<<(std::ostream &os, const Particle &p) {
    os << "Particle :" << std::endl
       << " - mass [GeV/c²]: " << p.mass() << std::endl
       << " - charge [C]: " << p.charge() << std::endl
       << " - position [m]: " << p.position() << std::endl
       << " - longitudinal position [m]: " << p.longitudinalPosition() << std::endl
       << " - radial position [m] " << p.radialPosition().r() << std::endl
       << " - gamma : " << p.gamma() << std::endl
       << " - energy [GeV]: " << p.energy() << std::endl
       << " - speed [m/s]: " << p.speed() << std::endl
       << " - corrected force [N]: " << p.lastForce() << std::endl
       << " - Number of turns: " << p.nbrOfTurns() << std::endl;
    return os;
}
