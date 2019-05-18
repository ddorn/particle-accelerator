//
// Created by Gabin on 04.04.2019.
//

#include <Beam.h>

#include "Beam.h"

using namespace std;

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

void Beam::updateEmittance() {
    if (nbrMacroParticles_ == 0) return;

    // Calculate emittance in relation to the z-axis
    double zPositions(0);
    double zSpeeds(0);
    double zProductPosSpeeds(0);
    for(const auto& p : macroParticles_){
        zPositions += p->position().z() * p->position().z();
        zSpeeds += p->speed().z() * p->speed().z();
        zProductPosSpeeds += p->position().z() * p->speed().z();
    }
    emittanceZ_ = sqrt((zPositions * zSpeeds - zProductPosSpeeds * zProductPosSpeeds) / nbrMacroParticles_ / nbrMacroParticles_);
    A11Z_ = zSpeeds / nbrMacroParticles_ / emittanceZ_;
    A12Z_ = zProductPosSpeeds / nbrMacroParticles_ / emittanceZ_;
    A22Z_ = zPositions / nbrMacroParticles_ / emittanceZ_;

    //calculate emittance in relation to the radial-xy-axis
    double rPositions(0);
    double rSpeeds(0);
    double rProductPosSpeeds(0);
    for(const auto& p : macroParticles_){
        RadialVec3D pos(p->radialPosition());
        RadialVec3D speed(p->radialSpeed());
        rPositions += pos.r() * pos.r();
        rSpeeds += speed.r() * speed.r();
        rProductPosSpeeds += pos.r() * speed.r();
    }
    emittanceR_ = sqrt((rPositions * rSpeeds - rProductPosSpeeds * rProductPosSpeeds) / nbrMacroParticles_ / nbrMacroParticles_);
    A11R_ = rSpeeds / nbrMacroParticles_ / emittanceR_;
    A12R_ = rProductPosSpeeds / nbrMacroParticles_ / emittanceR_;
    A22R_ = rPositions / nbrMacroParticles_ / emittanceR_;
}


std::ostream &operator<<(std::ostream &os, Beam const &beam) {
    os << " number of particles : " << beam.nbrParticles() << endl;
    os << " Beam emittance r : " << beam.emittanceR() << endl;
    os << " Beam emittance z : " << beam.emittanceZ() << endl;

    return os;
}
