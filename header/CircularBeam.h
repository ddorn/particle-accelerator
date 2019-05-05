//
// Created by Gabin on 07.04.2019.
//

#ifndef PARTICLEACCELERATOR_CIRCULARBEAM_H
#define PARTICLEACCELERATOR_CIRCULARBEAM_H

#include "Beam.h"

class CircularBeam : public Beam {
public:
    CircularBeam(const Particle &refParticle_, size_t lambda_, size_t nbrMacroParticles) : Beam(refParticle_, lambda_,
                                                                                                nbrMacroParticles) { generateParticles(); }

private:
    void generateParticles();
};

#endif //PARTICLEACCELERATOR_CIRCULARBEAM_H
