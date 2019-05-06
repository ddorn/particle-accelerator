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
            element_ = element()->nextElement();
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream &os, const Particle &partic) {
    os << "Particle :" << std::endl
        << " - mass : " << partic.mass() << " GeV / c²" << std::endl
        << " - charge : " << partic.charge() << " C" << std::endl
        << " - position : " << partic.position() << std::endl
        << " - gamma : " << partic.gamma() << std::endl
        << " - energy : " << partic.energy() << " GeV" << std::endl
        << " - speed : " << partic.speed() << " m/s" << std::endl
        << " - corrected force : " << partic.lastForce() << std::endl;
    return os;
}
