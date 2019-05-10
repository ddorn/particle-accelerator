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
        cout << "Axis was zero but this shouldn't happen" << endl;
        return;
    }

    force_ += force.rotate(axis, angle);

}

void Particle::evolve(double dt) {
    speed_ += dt * force_ / (gamma() * massSI());
    position_ += dt * speed_;
    lastForce_ = force_;  // for printing
    force_ *= 0;  // We reuse the same object
}

bool Particle::updateElement() {
    if (element()->collideBorder(position())) return false;

    // [e3, pos, speed] is positive with right hand rule aka CCW motion
    bool clockwise(Vector3D::e3.tripleProduct(position(), speed()) < 0);

    if (element()->isOut(position(), clockwise)) {
        if (element()->nextElement() == nullptr) return false;

        // update to the correct next element
        element_ = clockwise ? element()->nextElement()
                             : element()->previousElement();
        // Count a turn if again in the element it started
        if (element_ == spawn_) turns += 1;
    }

    return true;
}

std::ostream& operator<<(std::ostream &os, const Particle &partic) {
    os << "Particle :" << std::endl
        << " - mass [GeV/c²]: " << partic.mass() << std::endl
        << " - charge [C]: " << partic.charge() << std::endl
        << " - position [m]: " << partic.position() << std::endl
        << " - gamma : " << partic.gamma() << std::endl
        << " - energy [GeV]: " << partic.energy() << std::endl
        << " - speed [m/s]: " << partic.speed() << std::endl
        << " - corrected force [N]: " << partic.lastForce() << std::endl;
    return os;
}
