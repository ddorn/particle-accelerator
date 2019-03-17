//
// Created by diego on 3/17/19.
//

#ifndef PARTICLEACCELERATOR_ACCELERATOR_H
#define PARTICLEACCELERATOR_ACCELERATOR_H

#include <vector>
#include <iostream>
#include "../header/Particle.h"
#include "../header/Element.h"

class Accelerator {
private:
    std::vector<Element> elements_;
    std::vector<Particle> particles_;

public:
    Accelerator() = default;
    Accelerator(const Accelerator &other) = delete;
    void operator=(const Accelerator & other) = delete;

    /**
     * Add a new particle in the accelerator.
     * @param particle Particle to add.
     */
    void add(const Particle &particle) { particles_.push_back(particle); }
    /**
     * Add a new Element at the end of the accelerator.
     * @param element Element to add.
     */
    void add(const Element &element) { elements_.push_back(element); }

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
    void evolve();

    const std::vector<Particle> &Particles() const { return particles_; }
    const std::vector<Element> &Elements() const { return elements_; }
};

std::ostream& operator<<(std::ostream& os, const Accelerator &accelerator);


#endif //PARTICLEACCELERATOR_ACCELERATOR_H
