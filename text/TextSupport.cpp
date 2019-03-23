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
