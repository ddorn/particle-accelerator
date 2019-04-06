//
// Created by Gabin on 04.04.2019.
//

#include <Beam.h>

#include "Beam.h"


double Beam::meanEnergy() const {
    double sum(0);
    for(const auto& particle : macroParticles_){
        sum += particle->energy();
    }
    return sum / nbrParticles_;
}

double Beam::meanDistancesSqrd() const {
    double sum(0);
    for(const auto& particle : macroParticles_){
        sum += particle->radialDistanceSqrd();
    }
    return sum / macroParticles_.size();
}

double Beam::meanVelocitiesSqrd() const {
    double sum(0);
    for(const auto& particle : macroParticles_){
        sum += particle->radialVelocitySqrd();
    }
    return sum / macroParticles_.size();
}

double Beam::meanDistancesVelocities() const {
    double sum(0);
    for(const auto& particle : macroParticles_){
        sum += sqrt(particle->radialDistanceSqrd() * particle->radialVelocitySqrd());
    }
    return sum / macroParticles_.size();
}

double Beam::emittance() const {
    return sqrt(meanDistancesSqrd() * meanVelocitiesSqrd() - meanDistancesVelocities() * meanDistancesVelocities());
}

double Beam::A11() const {
    return meanVelocitiesSqrd() / emittance();
}

double Beam::A12() const {
    return -meanDistancesVelocities() / emittance();
}

double Beam::A22() const {
    return meanDistancesSqrd() / emittance();
}
