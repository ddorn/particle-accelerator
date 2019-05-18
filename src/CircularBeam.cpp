//
// Created by Gabin on 07.04.2019.
//

#include "CircularBeam.h"
#include <random>


void CircularBeam::generateParticles(double standardDeviation, int rng) {
    std::default_random_engine gen(rng);
    std::normal_distribution<double> distribution_(0, standardDeviation);
    Element* element(refParticle_.element());
    double s(0);
    RadialVec3D radialPosition(refParticle_.radialPosition());
    RadialVec3D radialSpeed(refParticle_.radialSpeed());
    double totalLength(0);

    do {
        totalLength += element->length();
        element = element->nextElement();
    } while (element != refParticle_.element());

    double ds(totalLength / nbrMacroParticles_);

    do {
        if (s >= element->length()) {
            s -= element->length();
            element = element->nextElement();
        }
        RadialVec3D position(radialPosition.r() + distribution_(gen), s + distribution_(gen), radialPosition.z() + distribution_(gen));
        addMacroParticle(element->absolutePosition(position), element->absoluteSpeed(position, radialSpeed),
                         element);
        s += ds;
    } while (macroParticles_.size() < nbrMacroParticles_);
}