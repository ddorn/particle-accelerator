//
// Created by diego on 3/17/19.
//

#include <iostream>
#include "TextSupport.h"

using namespace std;

void TextSupport::draw(const Particle &particle) {
    ostream_ << particle << endl;
}

void TextSupport::draw(const Element &element) {
    ostream_ << element << endl;
}

void TextSupport::draw(const Vector3D &d) {
    ostream_ << d << endl;
}

void TextSupport::draw(const Dipole &dipole) {
    ostream_ << dipole << endl;
}

void TextSupport::draw(const Accelerator &accelerator) {
    ostream_ << accelerator << endl;
}

void TextSupport::draw(const CurvedElement &element) {
    ostream_ << element << endl;

}

void TextSupport::draw(const Quadrupole &quadrupole) {
    ostream_ << quadrupole << endl;

}

void TextSupport::draw(const StraightElement &element) {
    ostream_ << element << endl;
}

void TextSupport::draw(const Segment &segment) {
    ostream_ << segment << endl;
}

void TextSupport::draw(const Beam &beam) {
    ostream_ << beam << endl;
}

