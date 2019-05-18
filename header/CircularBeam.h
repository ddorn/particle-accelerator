//
// Created by Gabin on 07.04.2019.
//

#ifndef PARTICLEACCELERATOR_CIRCULARBEAM_H
#define PARTICLEACCELERATOR_CIRCULARBEAM_H

#include "Beam.h"

/**
 * This class is used to generate particles
 * regularly spaced around the accelerator.
 */

class CircularBeam : public Beam {
public:
    CircularBeam(const Particle &refParticle_, size_t lambda_, size_t nbrMacroParticles, double standardDeviation = 0.01, int rng = 42) : Beam(refParticle_, lambda_,
                                                                                                nbrMacroParticles) { generateParticles(standardDeviation, rng); }

private:
    void generateParticles(double standardDeviation, int rng);
};

#endif //PARTICLEACCELERATOR_CIRCULARBEAM_H
