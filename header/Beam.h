//
// Created by Gabin on 04.04.2019.
//

#ifndef PARTICLEACCELERATOR_BEAM_H
#define PARTICLEACCELERATOR_BEAM_H

#include "Particle.h"
#include "Element.h"
#include <vector>
#include <memory>


typedef std::vector<std::unique_ptr<Particle>> ParticleVector;

/**
 * The beams will serve to inject particles and
 * to analyze their evolution in the accelerator.
 * To diminish the number of computations, the beam
 * contains macroparticles, each one representing a group
 * of particles.
 *
 */

class Beam{
public:
    /**
     * @return the mean energy between the real particles. Unit : GeV
     */
    double meanEnergy() const;
    /**
     * It is a measure for
     * the average spread of particle coordinates
     * in position-and-momentum phase space
     * @return emittance. Unit : c * s
     */
    double emittance() const;
    /**
     * A11, A12 and A22 are coefficients which describe the ellipsis
     * of the beam in position-and-momentum phase space.
     */
    double A11() const;
    double A12() const;
    double A22() const;
    /**
     * @return the ratio between the real particles and the macroparticles,
     * ie. the number of real particles in a macroparticle.
     */
    double lambda() const { return double(nbrParticles_) / macroParticles_.size(); };

    void evolve(double dt = 0.01);

private:
    Particle refParticle_;
    /**
     * The number of real particles
     */
    int nbrParticles_;
    /**
     * One macroparticle simulates lambda real particles
     */
    ParticleVector macroParticles_;
    /**
     * @return mean radial distance of the particles
     */
    double meanDistancesSqrd() const;
    /**
     * @return mean radial velocity of the particles
     */
    double meanVelocitiesSqrd() const;
    /**
     * @return mean of the product of the radial distance
     *  and radial velocity of the particles
     */
    double meanDistancesVelocities() const;

    void removeMacroParticle(size_t i);

};



#endif //PARTICLEACCELERATOR_BEAM_H