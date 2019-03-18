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
        p.addMagneticForce(Vector3D(0, 0, 1), dt);
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
