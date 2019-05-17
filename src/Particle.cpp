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
//    cout << b << endl;
//    cout << "Champ: " << force << endl;

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
    std::cout << charge() * e << std::endl;
}

void Particle::evolve(double dt) {
    speed_ += dt * force_ / (gamma() * massSI());
    position_ += dt * speed_;
    lastForce_ = force_;  // for printing
    force_ *= 0;  // We reuse the same object
}

bool Particle::updateElement() {
    if (element()->collideBorder(position())){
        isAlive_ = false;
        return false;
    }

    if (element()->isOut(position(), clockwise())) {
        if (element()->nextElement() == nullptr){
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
    addMagneticForce(p.magneticFieldAt(position()), dt);
    addElectricForce(p.electricFieldAt(position()));
    p.addMagneticForce(magneticFieldAt(p.position()), dt);
    p.addElectricForce(electricFieldAt(p.position()));
}

std::ostream& operator<<(std::ostream &os, const Particle &partic) {
    os << "Particle :" << std::endl
       << " - mass [GeV/c²]: " << partic.mass() << std::endl
       << " - charge [C]: " << partic.charge() << std::endl
       << " - position [m]: " << partic.position() << std::endl
       << " - longitudinal position [m]: " << partic.longitudinalPosition() << std::endl
       << " - gamma : " << partic.gamma() << std::endl
       << " - energy [GeV]: " << partic.energy() << std::endl
       << " - speed [m/s]: " << partic.speed() << std::endl
       << " - corrected force [N]: " << partic.lastForce() << std::endl
       << " - Number of turns: " << partic.nbrOfTurns() << std::endl;
    return os;
}
