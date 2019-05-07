//
// Created by diego on 5/6/19.
//

#include "Particle.h"
#include "constants.h"

using namespace constants;
using namespace std;

double Particle::velocityFromEnergy(double energy, double mass) const {
    double a = LIGHT_SPEED * sqrt(1 - mass * mass / (energy * energy));
    std::cout << a << energy << " " << mass<< endl;
    return a;
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
    if (element()->isOut(position())) {
        if (element()->nextElement() == nullptr) {
            return false;
        } else {
            cout << "Depasse et mtn dans : " << *element()->nextElement();
            element_ = element()->nextElement();
        }
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
