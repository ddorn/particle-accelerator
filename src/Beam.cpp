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


double Beam::emittanceZ() const {
    double zPositions(0);
    double zSpeeds(0);
    double productPosSpeeds(0);
    for(const auto& p : macroParticles_){
        zPositions += p->position().z() * p->position().z();
        zSpeeds += p->speed().z() * p->speed().z();
        productPosSpeeds += p->position().z() * p->speed().z();
    }
    return sqrt((zPositions * zSpeeds - productPosSpeeds * productPosSpeeds) / nbrMacroParticles_ / nbrMacroParticles_);
}

double Beam::emittanceR() const {
    double rPositions(0);
    double rSpeeds(0);
    double productPosSpeeds(0);
    for(const auto& p : macroParticles_){
        RadialVec3D pos(p->radialPosition());
        RadialVec3D speed(p->radialSpeed());
        rPositions += pos.r() * pos.r();
        rSpeeds += speed.r() * speed.r();
        productPosSpeeds += pos.r() * speed.r();
    }
    return sqrt((rPositions * rSpeeds - productPosSpeeds * productPosSpeeds) / nbrMacroParticles_ / nbrMacroParticles_);
}

double Beam::A11R() const {
    double rSpeeds(0);
    for(const auto& p : macroParticles_){
        RadialVec3D speed(p->radialSpeed());
        rSpeeds += speed.r() * speed.r();
    }
    return rSpeeds / nbrMacroParticles_ / emittanceR();
}

double Beam::A12R() const {
    double productPosSpeeds(0);
    for(const auto& p : macroParticles_){
        productPosSpeeds += p->radialPosition().r() * p->radialSpeed().r();
    }
    return productPosSpeeds / nbrMacroParticles_ / emittanceR();
}

double Beam::A22R() const {
    double zPositions(0);
    for(const auto& p : macroParticles_){
        RadialVec3D pos(p->radialPosition());
        zPositions += pos.r() * pos.r();
    }
    return zPositions / nbrMacroParticles_ / emittanceR();
}

double Beam::A11Z() const {
    double zSpeeds(0);
    for(const auto& p : macroParticles_){
        zSpeeds += p->speed().z() * p->speed().z();
    }
    return zSpeeds / nbrMacroParticles_ / emittanceZ();
}

double Beam::A12Z() const {
    double productPosSpeeds(0);
    for(const auto& p : macroParticles_){
        productPosSpeeds += p->speed().z() * p->position().z();
    }
    return productPosSpeeds / nbrMacroParticles_ / emittanceZ();
}

double Beam::A22Z() const {
    double rPositions(0);
    for(const auto& p : macroParticles_){
        rPositions += p->position().z() * p->position().z();
    }
    return rPositions / nbrMacroParticles_ / emittanceZ();
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

void Beam::addMacroParticle(const Vector3D &position, const Vector3D &direction, Element* element) {
    if (nbrMacroParticles_ > macroParticles_.size()) {
        macroParticles_.push_back(make_unique<Particle>(refParticle_.mass(),
                                                        refParticle_.charge(),
                                                        refParticle_.energy(),
                                                        position,
                                                        direction,
                                                        element,
                                                        refParticle_.color()));
    }
}

void Beam::removeDeadParticles() {
    for(size_t i(0); i < macroParticles().size(); ++i){
        if(!macroParticles()[i]->isAlive()){
            swap(macroParticles_[i], macroParticles_.back());
            macroParticles_.pop_back();
        }
    }
}


std::ostream &operator<<(std::ostream &os, Beam const &beam) {
    os << " Beam emittance r : " << beam.emittanceR() << endl;
    os << " Beam emittance z : " << beam.emittanceZ() << endl;
    for (auto const& macro : beam.macroParticles()) {
        os << *macro << endl;
    }
    return os;
}
