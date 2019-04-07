//
// Created by Gabin on 07.04.2019.
//

#include "CircularBeam.h"


void CircularBeam::generateParticles() {
    const Element* element(refParticle_.element());
    double s(0);
    Vector3D radialPosition(refParticle_.radialPosition());
    Vector3D radialSpeed(refParticle_.radialSpeed());
    double totalLength(0);

    do{
        totalLength += element->length();
        element = element->nextElement();
    } while(element != refParticle_.element());

    double ds(totalLength / nbrMacroParticles_);

    do{
        if(s >= element->length()){
            s -= element->length();
            element = element->nextElement();
        }
        Vector3D position(s, radialPosition.y(), radialPosition.z());
        addMacroParticle(element->absolutePosition(position), element->absoluteSpeed(position, radialSpeed),
                element);
        s += ds;
    } while(macroParticles_.size() < nbrMacroParticles_);

}