//
// Created by diego on 3/17/19.
//


#include "Accelerator.h"
#include "Segment.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "Sextupole.h"
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
    for (const auto &e : accelerator.elements()) {
        os << *e << endl;
    }
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
            cout << particles_[i]->nbrOfTurn() << endl;
            swap(particles_[i], particles_.back());
            particles_.pop_back();
        } else {
            ++i;
        }
    }


}

bool Accelerator::addSegment(const Vector3D &exit, double radius) {
    if (!acceptableNextElement(exit, radius)) return false;

    elements_.push_back(std::make_unique<Segment>(nextStart(), exit, radius, nullptr));
    linkElements();

    return true;
}

bool Accelerator::addDipole(const Vector3D &exit, double radius, double curvature, double magneticFieldIntensity) {
    if (!acceptableNextElement(exit, radius)
        || fabs(curvature) < Vector3D::getPrecision()) return false;

    elements_.push_back(std::make_unique<Dipole>(nextStart(), exit, radius, nullptr, curvature,
                                                 magneticFieldIntensity));
    linkElements();
    return true;
}

bool Accelerator::addDipole(const Vector3D &exit, double radius, double curvature, double mass, double charge,
                            double energy) {
    if (!acceptableNextElement(exit, radius)
        || fabs(curvature) < Vector3D::getPrecision())
        return false;
    if (mass <= 0) return false;
    if (energy <= 0) return false;
    if (charge == 0) return false;

    elements_.push_back(std::make_unique<Dipole>(nextStart(), exit, radius, nullptr, curvature, mass, charge, energy));
    linkElements();
    return true;
}

bool Accelerator::addQuadrupole(const Vector3D &exit, double radius, double magneticFieldIntensity) {
    if (!acceptableNextElement(exit, radius)) return false;

    elements_.push_back(std::make_unique<Quadrupole>(nextStart(), exit, radius, nullptr, magneticFieldIntensity));
    linkElements();
    return true;
}

bool Accelerator::addSextupole(const Vector3D &exit, double radius, double magneticlFieldIntensity) {
    if (!acceptableNextElement(exit, radius)) return false;

    elements_.push_back(std::make_unique<Sextupole>(nextStart(), exit, radius, nullptr, magneticlFieldIntensity));
    linkElements();
    return true;
}

bool Accelerator::addFODO(const Vector3D &exit, double quadrupoleLength, double radius, double magneticFieldIntesity) {
    if (!acceptableNextElement(exit, radius)) return false;
    Vector3D dir(~(exit - nextStart()));

    double length((nextStart() - exit).norm());
    double segmentLength(length / 2.0 - quadrupoleLength);

    addQuadrupole(nextStart() + quadrupoleLength * dir, radius, magneticFieldIntesity);
    addSegment(nextStart() + segmentLength * dir, radius);
    addQuadrupole(nextStart() + quadrupoleLength * dir, radius, -magneticFieldIntesity);
    addSegment(exit, radius);

    return true;
}

void Accelerator::linkElements() {
    if (elements().size() < 2) return;

    elements_[elements().size() - 2]->setNextElement(elements().back().get());
    if (isClosed()) {
        elements_.back()->setNextElement(elements_.front().get());
    }
}

bool Accelerator::isClosed() const {
    return not(elements().empty()) and elements().back()->exit() == start_;
}

bool Accelerator::acceptableNextElement(const Vector3D &exit, double radius) const {
    if (radius <= 0) return false;
    if (exit == nextStart()) return false;
    if (exit.z() != 0) return false;
    return !isClosed();
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
