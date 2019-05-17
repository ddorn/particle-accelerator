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

double Accelerator::MIN_DIST(1e-3);

std::ostream &operator<<(std::ostream &os, const Accelerator &accelerator) {
    os << "Accelerator:" << endl
       << " Beams:" << endl;
    for (const auto &b : accelerator.beams()) {
        os << *b << endl;
    }
    os << " Particles:" << endl;
    for (const auto &p : *accelerator.particles()) {
        cout << *p.particle() << endl;
    }
//    for (const auto &e : accelerator.elements()) {
//        os << *e << endl;
//    }
    return os;
}

void Accelerator::evolve(double dt) {

    for (auto& n : *particles_) {
        n.particle()->addElementMagneticForce(dt);
        for (Node::iterator it(n.next()); it != Node::iterator(&n) and (fabs(it->position() - n.position()) < MIN_DIST or
                                    fabs(it->position() + length() - n.position()) < MIN_DIST); ++it) {
            if (!it->isHead()){
                n.particle()->particleInteraction(*(it->particle()), dt);
            }
        }
    }

    for (Node::iterator it(particles_->begin()); it != particles_->end(); ++it) {
        it->particle()->evolve(dt);
        if (!it->particle()->updateElement()) {
            --it;
            it->removeNextNode();
        }
    }

    updateParticles();

    for (auto& mrBeam : beams_) {
        mrBeam->removeDeadParticles();
    }

    // Remove beams with no particles
    size_t i(0);
    while (i < beams_.size()) {
        if (beams_[i]->macroParticles().empty()) {
            swap(beams_[i], beams_.back());
            beams_.pop_back();
        } else {
            ++i;
        }
    }
    /*

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
*/

}

bool Accelerator::addSegment(const Vector3D &exit, double radius) {
    if (!acceptableNextElement(exit, radius)) return false;

    addElement(std::make_unique<Segment>(nextStart(), exit, radius, length()));

    return true;
}

bool Accelerator::addDipole(const Vector3D &exit, double radius, double curvature, double magneticFieldIntensity) {
    if (!acceptableNextElement(exit, radius)
        || fabs(curvature) < Vector3D::getPrecision()) return false;

    addElement(std::make_unique<Dipole>(nextStart(), exit, radius, curvature,
                                                 magneticFieldIntensity, length()));
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

    addElement(std::make_unique<Dipole>(nextStart(), exit, radius,  curvature, mass, charge, energy, length()));
    return true;
}

bool Accelerator::addQuadrupole(const Vector3D &exit, double radius, double magneticFieldIntensity) {
    if (!acceptableNextElement(exit, radius)) return false;

    addElement(std::make_unique<Quadrupole>(nextStart(), exit, radius,  magneticFieldIntensity, length()));
    return true;
}

bool Accelerator::addSextupole(const Vector3D &exit, double radius, double magneticlFieldIntensity) {
    if (!acceptableNextElement(exit, radius)) return false;

    addElement(std::make_unique<Sextupole>(nextStart(), exit, radius,  magneticlFieldIntensity, length()));
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
    for(const auto& p : beams_.back()->macroParticles()){
        addParticle(p);
    }

    return true;
}

Element *Accelerator::elementFromPosition(const Vector3D &position) const {
    for(auto& e : elements()){
        if(Vector3D::e3.tripleProduct(position, e->exit()) < 0 and Vector3D::e3.tripleProduct(position, e->start()) > 0){
            return e.get();
        }
    }
    return nullptr;
}

void Accelerator::updateParticles() const {
    for (auto &n : *particles_) n.updatePosition();

    Node *prevNode(particles_->previous());
    Node *nextNode(particles_->next());
    bool exchange(false);
    if (prevNode->previousPosition() - prevNode->position() > length() / 2) {
        prevNode->exchangePlace(particles_.get());
        exchange = true;
    }
    if (nextNode->position() - nextNode->previousPosition() > length() / 2) {
        nextNode->exchangePlace(particles_.get());
        if (exchange) {
            particles_->exchangePlace(prevNode); // It's a bit ugly, but we will upgrade it later #TODO
        }
    }


    Node *p(particles_->next());
    while (!p->isHead()) {
        nextNode = p->next();
        if (!nextNode->isHead() and nextNode->position() < p->position()) {
            p->exchangePlace(nextNode);
        } else {
        }
        p = nextNode;
    }
}

bool Accelerator::addParticle(double mass, double charge, double energy, const Vector3D &position,
                            const Vector3D &direction, const Vector3D &color) {
    Element* element(elementFromPosition(position));
    if(element == nullptr) return false;
    if (mass < 0) return false;

    particle_ptdr p(new Particle(mass, charge, energy, position, direction, element, color));
    particles_->insertNode(p);
    return true;
}

bool Accelerator::addParticle(particle_ptdr particle) {
    if (particle.get() == nullptr
        or particle->element() == nullptr
        or particle->mass() < 0)
        return false;
    particles_->insertNode(particle);
    return true;
}

void Accelerator::addElement(std::unique_ptr<Element> &&pdtr) {
    length_ += pdtr->length();
    elements_.push_back(std::move(pdtr));
    linkElements();
}
