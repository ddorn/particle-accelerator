//
// Created by Gabin on 04.04.2019.
//

#include <Beam.h>

#include "Beam.h"


double Beam::meanEnergy() const {
    double sum(0);
    for(const auto& particle : macroParticles_){
        sum += particle.energy();
    }
    return sum / nbrParticles_;
}

double Beam::emittance() const {
    double assEaters(0);
    return sqrt(assEaters); // TODO : I didn't understand what Chappi means.
}