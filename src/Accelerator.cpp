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


using namespace std;

double Accelerator::MIN_DIST(1e-3);

std::ostream &operator<<(std::ostream &os, const Accelerator &accelerator) {
    os << "Accelerator:" << endl;
    accelerator.showBeams(os);
    accelerator.showParticles(os);
    return os;
}

void Accelerator::showElements(ostream& os) const {
    os << " Elements :" << endl;
    for(const auto& e : elements_){
        os << *e << endl;
    }

}

void Accelerator::showBeams(std::ostream &os) const {
    os << " Beams :" << endl;
    for(const auto& b : beams_){
        os << *b << endl;
    }
}

void Accelerator::showParticles(std::ostream &os) const {
    os << " Particles :" << endl;
    for(const auto& p : *particles_) {
        os << *(p.particle()) << endl;
    }
}

void Accelerator::evolve(double dt) {

    // Add the magnetic and electric forces
    for (auto& n : *particles_) {
        n.particle()->addElementMagneticForce(dt);
        for (Node::iterator it(n.next()); it != Node::iterator(&n) and (fabs(it->position() - n.position()) < MIN_DIST or
                                    fabs(it->position() + length() - n.position()) < MIN_DIST); ++it) {
            if (!it->isHead()){
                n.particle()->particleInteraction(*(it->particle()), dt);
            }
        }
    }

    // Evolve particles and check whether they are dead
    for (Node::iterator it(particles_->begin()); it != particles_->end(); ++it) {
        if (it->particle()->evolve(dt)) {
            (--it)->removeNextNode();
        }
    }

    reorderParticleList();

    for (auto& mrBeam : beams_) {
        mrBeam->removeDeadParticles();
        mrBeam->updateEmittance();
    }

    // Remove beams with no particles
    size_t i(0);
    while (i < beams_.size()) {
        if (!beams_[i]->isAlive()) {
            swap(beams_[i], beams_.back());
            beams_.pop_back();
        } else {
            ++i;
        }
    }
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
    if (elements_.size() < 2) return;

    auto last = elements_.back().get();
    auto second = elements_[elements_.size() - 2].get();

    second->setNextElement(last);
    last->setPreviousElement(second);
    if (isClosed()) {
        last->setNextElement(elements_.front().get());
        elements_.front()->setPreviousElement(last);
    }
}

bool Accelerator::isClosed() const {
    return not(elements_.empty()) and elements_.back()->exit() == start_;
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
    if (elements_.empty()) return false;
    if (mass < 0) return false;
    if (lambda < 1) return false;

    Particle reference(mass, charge, energy, elements_.front()->start(), direction, elements_.front().get(), color);
    beams_.push_back(std::make_unique<CircularBeam>(reference, lambda, nbrMacroParticle, standardDeviation, rng));
    beams_.back()->generateParticles(*this);

    return true;
}

const Element * Accelerator::elementFromPosition(const Vector3D &position) const {
    for(auto& e : elements_){
        if(Vector3D::e3.tripleProduct(position, e->exit()) < 0 and Vector3D::e3.tripleProduct(position, e->start()) > 0){
            return e.get();
        }
    }
    return nullptr;
}

void Accelerator::reorderParticleList() const {
    for (auto &n : *particles_) n.updatePosition();

    Node* firstPreviousNode(particles_->previous());
    Node* firstNextNode(particles_->next());

    if(firstPreviousNode->previousPosition() - firstPreviousNode->position() > length() / 2) particles_->move(-1);
    while (particles_->previous()->previousPosition() - particles_->previous()->position() > length() / 2 and particles_->previous() != firstPreviousNode) {
        particles_->move(-1);
    }

    Node* nextNode(firstNextNode);
    if(nextNode->position() - nextNode->previousPosition() > length() / 2){
        nextNode = nextNode->next();
        firstNextNode->move(particles_->previous());
    }
    while (nextNode->position() - nextNode->previousPosition() > length() / 2 and nextNode != firstNextNode) {
        Node* nextNextNode(nextNode->next());
        nextNode->move(particles_->previous());
        nextNode = nextNextNode;
    }


    Node *p(particles_->next());
    while (!p->isHead()) {
        nextNode = p->next();
        if (!nextNode->isHead() and nextNode->position() < p->position()) {
            p->exchangePlace(nextNode);
            if(!nextNode->previous()->isHead()) p = nextNode->previous();
        } else {
        }
        p = nextNode;
    }
}

bool Accelerator::addParticle(double mass, double charge, double energy, const Vector3D &position,
                            const Vector3D &direction, const Vector3D &color) {
    const Element* element(elementFromPosition(position));
    if(element == nullptr) return false;
    if (mass < 0) return false;

    particles_->insertNode(make_shared<Particle>(mass, charge, energy, position, direction, element, color));
    return true;
}

bool Accelerator::addParticle(const particle_ptr& particle) {
    if (particle.get() == nullptr
        or particle->element() == nullptr
        or particle->mass() < 0) return false;

    particles_->insertNode(particle);
    return true;
}

void Accelerator::addElement(unique_ptr<Element> &&ptr) {
    length_ += ptr->length();
    elements_.push_back(std::move(ptr));
    linkElements();
}

bool Accelerator::isInside(const Vector3D &position) const {
    const Element* e(elementFromPosition(position));
    return e != nullptr && !e->collideBorder(position);
}
