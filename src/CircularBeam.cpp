//
// Created by Gabin on 07.04.2019.
//

#include "CircularBeam.h"


void CircularBeam::generateParticles() {
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
        RadialVec3D position(radialPosition.r(), s, radialPosition.z());
        addMacroParticle(element->absolutePosition(position), element->absoluteSpeed(position, radialSpeed),
                         element);
        s += ds;
    } while (macroParticles_.size() < nbrMacroParticles_);

}