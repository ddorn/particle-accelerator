//
// Created by Gabin on 10.05.2019.
//

#ifndef PARTICLEACCELERATOR_PROTON_H
#define PARTICLEACCELERATOR_PROTON_H

#include "Particle.h"

class Proton : public Particle{
public:
    Proton(double energy, Vector3D &position, Vector3D &direction, Element* element)
    : Particle(constants::M_PROTON, constants::C_PROTON, energy, position, direction, element) {}
};

class Electron : public Particle{
public:
    Electron(double energy, Vector3D &position, Vector3D &direction, Element* element)
    : Particle(constants::M_ELECTRON, constants::C_ELECTRON, energy, position, direction, element) {}
};

class Antiproton : public Particle{
public:
    Antiproton(double energy, Vector3D &position, Vector3D &direction, Element* element)
    : Particle(constants::M_PROTON, -constants::C_PROTON, energy, position, direction, element) {}
};

#endif //PARTICLEACCELERATOR_PROTON_H
