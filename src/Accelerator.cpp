//
// Created by diego on 3/17/19.
//


#include <Accelerator.h>

#include "Accelerator.h"
#include "Segment.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "CircularBeam.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const Accelerator &accelerator) {
    os << "Accelerator:" << endl
        << " Beams:" << endl;
    for (const auto &b : accelerator.beams()) {
        os << *b << endl;
    }
    for (const auto &p : accelerator.particles()) {
        os << *p << endl;
    }
//    for (const auto &e : accelerator.elements()) {
//        os << *e << endl;
//    }
    return os;
}

void Accelerator::evolve(double dt) {
    for (auto& mrBeam : beams_) {
        mrBeam->evolve(dt);
    }

    // Remove beams with no particles
    size_t i(0);
    while (i < beams_.size()) {
        if (beams_[i]->nbrParticles() == 0) {
            swap(beams_[i], beams_.back());
            beams_.pop_back();
        } else {
            ++i;
        }
    }

    // Update forces from the elements of the accelerator
    for (auto &p : particles_) {
        p->addMagneticForce(p->element()->magneticForceAt(p->position()), dt);
    }

    // And then compute the new position, speed and everything
    for (auto& p : particles_) {
        p->evolve(dt);
    }

    // Move particles_ between elements and remove them if needed
    i = 0;
    while (i < particles_.size()) {
        if (!particles_[i]->updateElement()) {
            swap(particles_[i], particles_.back());
            particles_.pop_back();
        } else {
            ++i;
        }
    }


}

bool Accelerator::addSegment(const Vector3D &exit, double radius) {
    if (not(acceptableNextElement(exit, radius))) { return false; }
    if (elements().empty()) {
        elements_.push_back(std::make_unique<Segment>(start_, exit, radius, nullptr));
    } else {
        elements_.push_back(std::make_unique<Segment>(elements().back()->exit(), exit, radius, nullptr));
        linkElements();
    }
    return true;
}

bool Accelerator::addDipole(const Vector3D &exit, double radius, double curvature, double magneticFieldIntensity) {
    if (not(acceptableNextElement(exit, radius)) or fabs(curvature) < Vector3D::getPrecision()) { return false; }
    if (elements().empty()) {
        elements_.push_back(std::make_unique<Dipole>(start_, exit, radius, nullptr, curvature, magneticFieldIntensity));
    } else {
        elements_.push_back(std::make_unique<Dipole>(elements().back()->exit(), exit, radius, nullptr, curvature,
                                                     magneticFieldIntensity));
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
        return radius > 0 and exit.z() == 0;
    }
    return not(isClosed() or radius <= 0 or exit == elements().back()->exit() or exit.z() != 0);
}

bool Accelerator::addCircularBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                                  size_t nbrMacroParticle, const Vector3D &color) {
    if (elements().empty()) return false;
    if (mass < 0) return false;
    if (lambda < 1) return false;

    Particle reference(mass, charge, energy, elements().front()->start(), direction, elements().front().get(), color);
    beams_.push_back(std::make_unique<CircularBeam>(reference, lambda, nbrMacroParticle));

    return true;
}

bool Accelerator::addBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                          const std::vector<Particle> &macroParticles, const Vector3D &color) {
    if (elements().empty()) return false;
    if (mass < 0) return false;
    if (lambda < 1) return false;

    Particle reference(mass, charge, energy, elements().front()->start(), direction, elements().front().get(), color);
    beams_.push_back(std::make_unique<Beam>(reference, lambda, macroParticles.size()));
    for(auto& p : macroParticles) {
        beams_.back()->addMacroParticle(p.position(), p.speed(), elements().front().get());
    }
    return true;
}