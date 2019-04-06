//
// Created by Gabin on 04.04.2019.
//

#ifndef PARTICLEACCELERATOR_BEAM_H
#define PARTICLEACCELERATOR_BEAM_H

#include "Particle.h"
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
    double A11() const;
    double A12() const;
    double A22() const;
    /**
     * @return the ratio between the real particles and the macroparticles
     */
    double lambda() const { return double(nbrParticles_) / macroParticles_.size(); };

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
    double meanDistancesSqrd() const;
    double meanVelocitiesSqrd() const;
    double meanDistancesVelocities() const;

};



#endif //PARTICLEACCELERATOR_BEAM_H