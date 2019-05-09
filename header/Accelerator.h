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
 * each particle. Each element is automatically
 * linked to the precedent, and if the last element
 * ends where the first element begins, the link
 * will be set automatically too. If the accelerator
 * is closed (the last element is linked to the first),
 * it is impossible to add a new element.
 * Authors: Diego Dorn & Gabin Kolly
 */

#ifndef PARTICLEACCELERATOR_ACCELERATOR_H
#define PARTICLEACCELERATOR_ACCELERATOR_H

#include <vector>
#include <iostream>
#include <memory>
#include <random>
#include "Particle.h"
#include "Element.h"
#include "Content.h"
#include "Support.h"
#include "CircularBeam.h"

typedef std::vector<std::unique_ptr<Element>> ElementVector;
typedef std::vector<std::unique_ptr<Beam>> BeamVector;

class Accelerator : public Content {
private:
    ElementVector elements_;
    BeamVector beams_;
    ParticleVector particles_;
    std::mt19937 rng;
    std::uniform_real_distribution<double> distribution;

    const Vector3D nextStart() const { return elements().empty() ? start_ : elements().back()->exit(); }

public:
    explicit Accelerator(const Vector3D& start = Vector3D()) : rng(42), distribution(-0.03, 0.03), start_(start){}
    Accelerator(const Accelerator &other) = delete;
    void operator=(const Accelerator & other) = delete;

    const ParticleVector &particles() const { return particles_; }

    /**
     * Cleanup the dust in the Accelerator and remove all particles.
     */
    void cleanBeam() { beams_.clear(); particles_.clear();}
    /**
     * Remove all the elements of the accelerator.
     * Warning: don't forget to recycle all this metal otherwise students will have good reasons to demonstrate
     */
    void cleanElements() { elements_.clear(); }

    /**
     * One small step for the accelerator, one giant leap for mankind.
     * Small is exactly 0.01 seconds.
     */
    void evolve(double dt = 1e-11);

    const BeamVector &beams() const { return beams_; }
    const ElementVector &elements() const { return elements_; }

    void draw(Support &support) const override { support.draw(*this); }

    /**
     * Add a segment. It begins where the last added element ends.
     * @return false if it cannot add this element.
     */
    bool addSegment(const Vector3D& exit, double radius);
    /**
     * Add a dipole. It begins where the last added element ends.
     * @return false if it cannot add this element.
     */
    bool addDipole(const Vector3D& exit, double radius, double curveture, double magneticFieldIntensity);
    bool addDipole(const Vector3D& exit, double radius, double curvature, double mass, double charge, double energy);
    /**
     * Add a quadrupole. It begins where the last added element ends.
     * @return false if it cannot add this element.
     */
    bool addQuadrupole(const Vector3D& exit, double radius, double magneticFieldIntensity);
    bool addFODO(const Vector3D &exit, double quadrupoleLength, double radius, double magneticFieldIntesity);
    bool addSextupole(const Vector3D &exit, double radius, double magneticlFieldIntensity);
    bool addBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                 const std::vector<Particle> &macroParticles, const Vector3D &color = Vector3D(1, 1, 1));

    bool addCircularBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                                      size_t nbrMacroParticle, const Vector3D &color = Vector3D(1, 1, 1));
    void addParticle(const Particle &p) { particles_.push_back(std::make_unique<Particle>(p)); }
    /**
    * @return if the last element ends where the first element begins.
    */
    bool isClosed() const;
    double length() const;
private:
    /**
     * Add a new particle in the accelerator.
     * @param particle Particle to add.
     */
    Vector3D start_;
    /**
     * Link the two last elements
     * and control if the last element
     * must be linked to the first.
     */
    void linkElements();

    /**
     * @return if the element can be added to the accelerator, i.e.
     * if the exit is not the entree, if the radius is strictly positive and
     * if the element is in the xy plane.
     */
    bool acceptableNextElement(const Vector3D& exit, double radius) const;

};

std::ostream& operator<<(std::ostream& os, const Accelerator &accelerator);


#endif //PARTICLEACCELERATOR_ACCELERATOR_H
