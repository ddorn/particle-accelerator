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
private:
    int rng;
    double standardDeviation;
public:
    CircularBeam(const Particle &refParticle_, size_t lambda_, size_t nbrMacroParticles,
                 double standardDeviation = 1e-8, int rng = 42)
            : Beam(refParticle_, lambda_,
                   nbrMacroParticles), rng(rng), standardDeviation(standardDeviation) {}

    void generateParticles(Accelerator &accelerator) override;
};

#endif //PARTICLEACCELERATOR_CIRCULARBEAM_H
