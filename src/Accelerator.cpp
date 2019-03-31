//
// Created by diego on 3/17/19.
//

#include "Accelerator.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Accelerator &accelerator) {
    os << "Accelerator:" << endl
        << " Particles:" << endl;
    for (const auto &p : accelerator.particles()) {
        os << *p << endl;
    }
    os << " Elements:" << endl;
    for (const auto &e : accelerator.elements()) {
        os << *e << endl;
    }
    return os;
}

void Accelerator::evolve(double dt) {

    // We add all the forces first
    for (auto& p : particles_) {
        // This is just a placeholder to see nice things
        Vector3D champ = Vector3D(0, 0, 1) ;
        double scale = (champ * p->position());
//        double scale = p.position().norm();
        if (abs(scale) > 1e-4) champ /= scale;

        p->addMagneticForce(champ, dt);
    }

    // And then compute the new position, speed and everything
    for (auto& p : particles_) {
        p->evolve(dt);
    }
}

void Accelerator::draw() {
    for (const auto &p : particles_) {
        support_->draw(*p);
    }
    for (const auto &e : elements_) {
        support_->draw(*e);
    }
}
