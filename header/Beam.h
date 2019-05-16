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
 * of particles.
 *
 */
class Beam : public Content {
public:
    Beam(const Particle &refParticle_, size_t lambda_, size_t nbrMacroParticles) : lambda_(lambda_),
                                                                                   nbrMacroParticles_(
                                                                                           nbrMacroParticles),
                                                                                   refParticle_(refParticle_) {}
   ParticleVector const& macroParticles() const { return macroParticles_; }

    /**
     * @return the mean energy between the real particles. Unit : GeV
     */
    double meanEnergy() const;

    /**
     * It is a measure for
     * the average spread of particle coordinates
     * in position-and-momentum phase space
     * @return emittance. Unit : m²/s
     */
    double emittanceZ() const;
    double emittanceR() const;

    /**
     * A11, A12 and A22 are coefficients which describe the ellipsis
     * of the beam in position-and-momentum phase space.
     */
    double A11R() const;

    double A12R() const;

    double A22R() const;

    double A11Z() const;

    double A12Z() const;

    double A22Z() const;

    /**
     * @return the ratio between the real particles and the macroparticles,
     * ie. the number of real particles in a macroparticle.
     */
    size_t lambda() const { return lambda_; };

    int nbrParticles() const { return int(ceil(lambda() * macroParticles_.size())); }

    void evolve(double dt = 0.01);

    void draw(Support &support) const override { support.draw(*this); }

    void removeMacroParticle(size_t i);

    void addMacroParticle(const Vector3D &position, const Vector3D &direction, Element *element);

    void removeDeadParticles();

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


};


std::ostream& operator<<(std::ostream &os, Beam const& beam);

#endif //PARTICLEACCELERATOR_BEAM_H