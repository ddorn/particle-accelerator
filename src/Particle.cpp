//
// Created by Gabin on 08.03.2019.
//

#include <cmath>
#include "../header/Particle.h"


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
