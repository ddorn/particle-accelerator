//
// Created by Gabin on 04.04.2019.
//

#include <Beam.h>

#include "Beam.h"

using namespace std;


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

void Beam::addMacroParticle(const Vector3D &position, const Vector3D &speed, Element* element) {
    if (nbrMacroParticles_ > macroParticles_.size()) {
        macroParticles_.push_back(make_unique<Particle>(refParticle_.mass(),
                                                        refParticle_.charge(),
                                                        position,
                                                        momentumFromSpeed(speed, refParticle_.mass()),
                                                        refParticle_.color(),
                                                        element));
    }
}



std::ostream &operator<<(std::ostream &os, Beam const &beam) {
    for (auto const& macro : beam.macroParticles()) {
        os << *macro << endl;
    }
    return os;
}
