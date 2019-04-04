//
// Created by Gabin on 04.04.2019.
//

#ifndef PARTICLEACCELERATOR_BEAM_H
#define PARTICLEACCELERATOR_BEAM_H

#include "Particle.h"
#include <vector>
#include <memory>


typedef std::vector<std::unique_ptr<Particle>> ParticleVector;

class Beam{
public:
    /**
     * @return the mean energy between the real particles
     */
    double meanEnergy() const;
    /**
     * Don't know what this shit is now
     * Wikipedia says : It is a measure for
     * the average spread of particle coordinates
     * in position-and-momentum phase space
     * @return
     */
    double emittance() const;
    /**
     * @return the
     */
    double lambda() const { return double(nbrParticles_) / macroParticles_.size(); };

private:
    Particle refParticle_;
    int nbrParticles_;
    ParticleVector macroParticles_;

};



#endif //PARTICLEACCELERATOR_BEAM_H