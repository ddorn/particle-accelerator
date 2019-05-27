//
// Created by Gabin on 04.04.2019.
//

#ifndef PARTICLEACCELERATOR_BEAM_H
#define PARTICLEACCELERATOR_BEAM_H

#include "Particle.h"
#include "Element.h"
#include "Content.h"
#include "Support.h"
#include <vector>
#include <memory>


typedef std::vector<std::shared_ptr<Particle>> ParticleVector;

/**
 * The beams will serve to inject particles and
 * to analyze their evolution in the accelerator.
 * To diminish the number of computations, the beam
 * contains macroparticles, each one representing a group
 * of particles. The particle of reference, given at the
 * creation of the beam, represents the mean characteristics
 * of the particles in the beam : energy, radial position and speed,
 * charge, mass.
 *
 */
class Beam : public Content {
public:
    Beam(const Particle &refParticle_, size_t lambda_, size_t nbrMacroParticles) : lambda_(lambda_),
                                                                                   nbrMacroParticles_(
                                                                                           nbrMacroParticles),
                                                                                   refParticle_(refParticle_)
                                                                                   { updateEmittance(); }
   ParticleVector const& macroParticles() const { return macroParticles_; } //TODO : give a list of particles


    /**
     * It is a measure for
     * the average spread of particle coordinates
     * in position-and-momentum phase space
     * @return emittance. Unit : m²/s
     */
    double emittanceZ() const { return emittanceZ_; }
    double emittanceR() const { return emittanceR_; }

    /**
     * A11, A12 and A22 are coefficients which describe the ellipsis
     * of the beam in position-and-momentum phase space.
     */
    double A11R() const { return A11R_; }

    double A12R() const { return A12R_; }

    double A22R() const { return A22R_; }

    double A11Z() const { return A11Z_; }

    double A12Z() const { return A12Z_; }

    double A22Z() const { return A22Z_; }

    /**
     * @return the ratio between the real particles and the macroparticles,
     * ie. the number of real particles in a macroparticle.
     */
    size_t lambda() const { return lambda_; };

    /**
     * @return the number of real particles
     */
    int nbrParticles() const { return int(ceil(lambda() * macroParticles_.size())); }

    void draw(Support &support) const override { support.draw(*this); }

    /**
     * Remove the macroparticle in the list at the place i.
     */
    void removeMacroParticle(size_t i);

    /**
     * Add a macroparticle
     */
    void addMacroParticle(const Vector3D &position, const Vector3D &direction, Element *element);

    /**
     * Remove all the macroparticles which collided with the border
     */
    void removeDeadParticles();

    /**
     * Update the value of the emittance, and of the coefficients A11, A12 and A22
     */
    void updateEmittance();

private:
    /**
     * The number of real particles in a macroparticle
     */
    size_t lambda_;


protected:
    size_t nbrMacroParticles_;
    /**
     * One macroparticle simulates lambda real particles
     */
    ParticleVector macroParticles_;
    Particle refParticle_;

    double emittanceZ_;
    double emittanceR_;

    double A11R_;

    double A12R_;

    double A22R_;

    double A11Z_;

    double A12Z_;

    double A22Z_;


};


std::ostream& operator<<(std::ostream &os, Beam const& beam);

#endif //PARTICLEACCELERATOR_BEAM_H