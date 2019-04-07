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
    return sum / nbrParticles();
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

void Beam::evolve(double dt) {

    // Update forces from the elements of the accelerator
    for (auto &p : macroParticles_) {
        p->addMagneticForce(p->element()->magneticForceAt(p->position()), dt);
    }

    // Move particles between elements and remove them if needed
    size_t i(0);
    while (i < macroParticles_.size()) {
        if (!macroParticles_[i]->updateElement()) {
            removeMacroParticle(i);
        } else {
            ++i;
        }
    }

//
//    // We add all the forces first
//    for (auto& p : particles_) {
//        // This is just a placeholder to see nice things
//        Vector3D champ = Vector3D(0, 0, 1) ;
//        double scale = (champ * p->position());
////        double scale = p.position().norm();
//        if (abs(scale) > 1e-4) champ /= scale;
//
//        p->addMagneticForce(champ, dt);
//    }

    // And then compute the new position, speed and everything
    for (auto& p : macroParticles_) {
        p->evolve(dt);
    }
}

void Beam::removeMacroParticle(size_t i) {
    nbrMacroParticles_ -= 1;
    // The order of particles doesn't matter,
    // so we put the particle we need to delete at the end
    // and then remove it
    swap(macroParticles_[i], macroParticles_.back());
    macroParticles_.pop_back();
}
