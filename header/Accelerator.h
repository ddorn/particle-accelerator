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

    void add(const Particle &particle) { particles_.push_back(particle); }
    void add(const Element &element) { elements_.push_back(element); }
    void cleanParticles() { particles_.clear(); }
    void cleanElements() { elements_.clear(); }
    void evolve();

    const std::vector<Particle> &Particles() const { return particles_; }
    const std::vector<Element> &Elements() const { return elements_; }
};

std::ostream& operator<<(std::ostream& os, const Accelerator &accelerator);


#endif //PARTICLEACCELERATOR_ACCELERATOR_H
