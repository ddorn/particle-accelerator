//
// Created by diego on 3/17/19.
//


#include "Accelerator.h"
#include "Segment.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "Sextupole.h"
#include "CircularBeam.h"
#include <chrono>
#include <Accelerator.h>


using namespace std;

std::ostream &operator<<(std::ostream &os, const Accelerator &accelerator) {
    os << "Accelerator:" << endl
        << " Beams:" << endl;
    for (const auto &b : accelerator.beams()) {
        os << *b << endl;
    }
    Node* p(accelerator.particles()->next());
    while(p != nullptr){
        os << *(p->particle()) << endl;
        p = p->next();
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
            cout << particles_[i]->nbrOfTurns() << endl;
            swap(particles_[i], particles_.back());
            particles_.pop_back();
        } else {
            ++i;
        }
    }


}

bool Accelerator::addSegment(const Vector3D &exit, double radius) {
    if (!acceptableNextElement(exit, radius)) return false;

    elements_.push_back(std::make_unique<Segment>(nextStart(), exit, radius));
    linkElements();

    return true;
}

bool Accelerator::addDipole(const Vector3D &exit, double radius, double curvature, double magneticFieldIntensity) {
    if (!acceptableNextElement(exit, radius)
        || fabs(curvature) < Vector3D::getPrecision()) return false;

    elements_.push_back(std::make_unique<Dipole>(nextStart(), exit, radius, curvature,
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

    elements_.push_back(std::make_unique<Dipole>(nextStart(), exit, radius,  curvature, mass, charge, energy));
    linkElements();
    return true;
}

bool Accelerator::addQuadrupole(const Vector3D &exit, double radius, double magneticFieldIntensity) {
    if (!acceptableNextElement(exit, radius)) return false;

    elements_.push_back(std::make_unique<Quadrupole>(nextStart(), exit, radius,  magneticFieldIntensity));
    linkElements();
    return true;
}

bool Accelerator::addSextupole(const Vector3D &exit, double radius, double magneticlFieldIntensity) {
    if (!acceptableNextElement(exit, radius)) return false;

    elements_.push_back(std::make_unique<Sextupole>(nextStart(), exit, radius,  magneticlFieldIntensity));
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

    auto last = elements().back().get();
    auto second = elements_[elements().size() - 2].get();

    second->setNextElement(last);
    last->setPreviousElement(second);
    if (isClosed()) {
        last->setNextElement(elements_.front().get());
        elements_.front()->setPreviousElement(last);
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
                                  size_t nbrMacroParticle, const Vector3D &color, double standardDeviation){
    return addCircularBeam(mass, charge, energy, direction, lambda, nbrMacroParticle, color, standardDeviation, int(std::chrono::system_clock::now().time_since_epoch().count() % 1000000));
}

bool Accelerator::addCircularBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                                  size_t nbrMacroParticle, const Vector3D &color, double standardDeviation, int rng) {
    if (elements().empty()) return false;
    if (mass < 0) return false;
    if (lambda < 1) return false;

    Particle reference(mass, charge, energy, elements().front()->start(), direction, elements().front().get(), color);
    beams_.push_back(std::make_unique<CircularBeam>(reference, lambda, nbrMacroParticle, standardDeviation, rng));

    return true;
}


double Accelerator::length() const {
    double l(0);
    for(auto &e : elements()){
        l += e->length();
    }
    return l;
}

Element *Accelerator::elementFromPosition(Vector3D &position) {
    for(auto& e : elements()){
        if(Vector3D::e3.tripleProduct(position, e->exit()) < 0 and Vector3D::e3.tripleProduct(position, e->start()) > 0){
            return e.get();
        }
    }
    return nullptr;
}

void Accelerator::updateParticles() const {
    Node* prevNode(particles()->previous());
    Node* nextNode(particles()->next());
    bool exchange(false);
    if(prevNode->previousPosition() - prevNode->position() > length() / 2){
        prevNode->exchangePlace(particles().get());
        exchange = true;
    }
    if(nextNode->position() - nextNode->previousPosition() > length() / 2){
        nextNode->exchangePlace(particles().get());
        if(exchange){
            particles()->exchangePlace(prevNode); // It's a bit ugly, but we will upgrade it later #TODO
        }
    }
    Node* p(particles()->next());
    while(!p->isHead()){
        nextNode = p->next();
        if(!nextNode->isHead() and nextNode->position() < p->position()){
            p->exchangePlace(nextNode);
        } else {
            p = nextNode;
        }
    }
}
