//
// Created by Gabin on 07.04.2019.
//

#ifndef PARTICLEACCELERATOR_CIRCULARBEAM_H
#define PARTICLEACCELERATOR_CIRCULARBEAM_H

#include "Beam.h"

class circularBeam : public Beam{
public:
    circularBeam(const Particle &refParticle_, double lambda_, size_t nbrMacroParticles) : Beam(refParticle_, lambda_,
            nbrMacroParticles) { generateParticles(); }

private:
    void generateParticles() override;
};

#endif //PARTICLEACCELERATOR_CIRCULARBEAM_H
