//
// Created by diego on 3/17/19.
//

#include "Accelerator.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Accelerator &accelerator) {
    os << "Accelerator:" << endl
        << " Particles:" << endl;
    for (auto p : accelerator.Particles()) {
        os << p << endl;
    }
    os << " Elements:" << endl;
    for (auto e : accelerator.Elements()) {
        os << e << endl;
    }
    return os;
}

void Accelerator::evolve(double dt) {
    for (auto& p : particles_) {
        // This is just a placeholder to see nice things
//        float dist = p.position().norm();
        Vector3D champ = Vector3D(-1, 0, 0) ;
        double scale = champ * p.position();
        if (abs(scale) > 1e-4) champ /= scale;

        p.addMagneticForce(champ, dt);
        p.evolve(dt);
    }
}

void Accelerator::draw() {
    for (auto p : particles_) {
        support_->draw(p);
    }
    for (auto e : elements_) {
        support_->draw(e);
    }
}
