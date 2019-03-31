#include <memory>

/**
 * This header defines the Accelerator class.
 *
 * The main purpose of this class is to simulate
 * a particle accelerator. It's the glue between
 * particles that run in the accelerator and the
 * elements of the accelerator that modify their
 * trajectories.
 *
 * The most important method is `evolve()`, that
 * simulates the whole system with a given step.
 *
 * In order to build a particle accelerator, one
 * needs to add each element one by one and then
 * each particle.
 *
 * Authors: Diego Dorn & Gabin Kolly
 */

#ifndef PARTICLEACCELERATOR_ACCELERATOR_H
#define PARTICLEACCELERATOR_ACCELERATOR_H

#include <vector>
#include <iostream>
#include <memory>
#include "Particle.h"
#include "Element.h"
#include "Content.h"
#include "Support.h"

typedef std::vector<std::unique_ptr<Element>> ElementVector;
typedef std::vector<std::unique_ptr<Particle>> ParticleVector;

class Accelerator : public Content {
private:
    ElementVector elements_;
    ParticleVector particles_;

public:
    explicit Accelerator(Support* s) : Content(s) {}
    Accelerator(const Accelerator &other) = delete;
    void operator=(const Accelerator & other) = delete;

    /**
     * Cleanup the dust in the Accelerator and remove all particles.
     */
    void cleanParticles() { particles_.clear(); }
    /**
     * Remove all the elements of the accelerator.
     * Warning: don't forget to recycle all this metal otherwise students will have good reasons to demonstrate
     */
    void cleanElements() { elements_.clear(); }

    /**
     * One small step for the accelerator, one giant leap for mankind.
     * Small is exactly 0.01 seconds.
     */
    void evolve(double dt = 0.01);

    const ParticleVector &particles() const { return particles_; }
    const ElementVector &elements() const { return elements_; }

    void draw() override;

    /**
     * Add a new Element at the end of the accelerator.
     *
     * Elements should be on the horizontal plane z=0,
     * and start at the end of the last element.
     * No checks are performed.
     *
     * @param element Element to add.
     */
    void add(Element* element) { elements_.push_back(std::unique_ptr<Element>(element)); }

    bool addParticle(double mass, double charge, const Vector3D &momentum, const Vector3D &color = Vector3D(0, 0, 1));

private:
    /**
     * Add a new particle in the accelerator.
     * @param particle Particle to add.
     */
    void add(Particle* particle) { particles_.push_back(std::unique_ptr<Particle>(particle)); }

};

std::ostream& operator<<(std::ostream& os, const Accelerator &accelerator);


#endif //PARTICLEACCELERATOR_ACCELERATOR_H
