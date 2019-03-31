//
// Created by diego on 3/17/19.
//

#include <Accelerator.h>

#include "Accelerator.h"
#include "Segment.h"
#include "Dipole.h"
#include "Quadrupole.h"

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

    // Update forces from the elements of the accelerator
    for (auto &p : particles()) {
        p->addMagneticForce(p->element()->magneticForceAt(p->position()), dt);
    }

    // Move particles between elements and remove them if needed
    size_t i(0);
    while (i < particles_.size()) {
        if (!particles_[i]->updateElement()) {
            // The order of particles doesn't matter,
            // so we put the particle we need to delete at the end
            // and then remove it
            swap(particles_[i], particles_.back());
            particles_.pop_back();
        } else {
            ++i;
        }
    }

//
//    // We add all the forces first
//    for (auto& p : particles_) {
//        // This is just a placeholder to see nice things
//        Vector3D champ = Vector3D(0, 0, 1) ;
//        double scale = (champ * p->position());
////        double scale = p.position().norm();
//        if (abs(scale) > 1e-4) champ /= scale;
//
//        p->addMagneticForce(champ, dt);
//    }

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

bool Accelerator::addParticle(double mass, double charge, const Vector3D &momentum, const Vector3D &color) {
    if (elements().empty()) return false;
    if (mass < 0) return false;

    particles_.push_back(std::make_unique<Particle>(mass,
                                                    charge,
                                                    elements_.front()->entree(),
                                                    momentum,
                                                    color,
                                                    elements_.front().get()
    ));

    return true;
}

bool Accelerator::addSegment(const Vector3D &exit, double radius) {
    if(not(acceptableNextElement(exit, radius))){return false;}
    if(elements().empty()){
        elements_.push_back(std::make_unique<Segment>(start_, exit, radius, nullptr));
    } else{
        elements_.push_back(std::make_unique<Segment>(elements().back()->exit(), exit, radius, nullptr));
        linkElements();
    }
    return true;
}

bool Accelerator::addDipole(const Vector3D &exit, double radius, double curvature, double magneticFieldIntensity) {
    if(not(acceptableNextElement(exit, radius)) or fabs(curvature) < Vector3D::getPrecision()){return false;}
    if(elements().empty()){
        elements_.push_back(std::make_unique<Dipole>(start_, exit, radius, nullptr, curvature, magneticFieldIntensity));
    } else{
        elements_.push_back(std::make_unique<Dipole>(elements().back()->exit(), exit, radius, nullptr, curvature, magneticFieldIntensity));
        linkElements();
    }
    return true;
}

bool Accelerator::addQuadrupole(const Vector3D &exit, double radius, double magneticFieldIntensity) {
    if(not(acceptableNextElement(exit, radius))){return false;}
    if(elements().empty()){
        elements_.push_back(std::make_unique<Quadrupole>(start_, exit, radius, nullptr, magneticFieldIntensity));
    } else{
        elements_.push_back(std::make_unique<Quadrupole>(elements().back()->exit(), exit, radius, nullptr, magneticFieldIntensity));
        linkElements();
    }
    return true;
}

void Accelerator::linkElements() {
    elements_[elements().size() - 2]->setNextElement(elements().back().get());
    if(isClosed()){
        elements_.back()->setNextElement(elements_.front().get());
    }
}

bool Accelerator::isClosed() const {
    return not(elements().empty()) and elements().back()->exit() == start_;
}

bool Accelerator::acceptableNextElement(const Vector3D &exit, double radius) const {
    if(elements().empty()){
        return radius <= 0;
    }
    return not(isClosed() or radius <= 0 or exit == elements().back()->exit());
}
