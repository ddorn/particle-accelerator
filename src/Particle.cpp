//
// Created by Gabin on 08.03.2019.
//

#include <cmath>
#include "../header/Particle.h"



const Vector3D Particle::speedFromMomentum(const Vector3D &momentum){return momentum / sqrt(mass*mass + momentum.normSquared() / (c*c));}
const Vector3D Particle::momentum() const{return getSpeed() * gamma() * getMass();}
double Particle::gamma() const{ return 1 / sqrt(1 - getSpeed().normSquared() / (c*c) );}
double Particle::energy() const{ return gamma() * getMass() * c*c;}

std::ostream &operator<<(std::ostream &os, const Particle &partic) {
    os << "Particle :" << std::endl << "- mass : " << partic.getMass() << std::endl << "- charge : " << partic.getElecCharge() <<
    std::endl << "- position : " << partic.getPosition() << std::endl << "- gamma : " << partic.gamma() << std::endl
     << "- momentum : " << partic.momentum() << std::endl << "- energy : " << partic.energy() << std::endl <<
     "- speed : " << partic.getSpeed() << std::endl;
    return os;
}
