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
#include "Node.h"

typedef std::vector<std::unique_ptr<Element>> ElementVector;
typedef std::vector<std::unique_ptr<Beam>> BeamVector;
typedef std::unique_ptr<Node> LinkedList;

class Accelerator : public Content {
private:
    ElementVector elements_;
    BeamVector beams_;
    LinkedList particles_;
    std::default_random_engine rng_;

    const Vector3D nextStart() const { return elements().empty() ? start_ : elements().back()->exit(); }

public:
    explicit Accelerator(const Vector3D& start = Vector3D(), int rng = 42) : rng_(rng), start_(start){}
    Accelerator(const Accelerator &other) = delete;
    void operator=(const Accelerator & other) = delete;

    const LinkedList &particles() const { return particles_; }

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
    /**
     * This method will create a dipole with the perfect magnetic field intensity, in function of
     * the mean mass, charge and energy of the particles.
     */
    bool addDipole(const Vector3D& exit, double radius, double curvature, double mass, double charge, double energy);
    /**
     * Add a quadrupole. It begins where the last added element ends.
     * @return false if it cannot add this element.
     */
    bool addQuadrupole(const Vector3D& exit, double radius, double magneticFieldIntensity);
    /**
     * Add a FODO cell.
     */
    bool addFODO(const Vector3D &exit, double quadrupoleLength, double radius, double magneticFieldIntensity);
    /**
     * Add a sextupole. It begins where the last added element ends.
     * @return false if it cannot add this element.
     */
    bool addSextupole(const Vector3D &exit, double radius, double magneticFieldIntensity);

    bool addCircularBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                                      size_t nbrMacroParticle, const Vector3D &color = Vector3D(1, 1, 1), double standardDeviation = 0.01);
    bool addCircularBeam(double mass, double charge, double energy, const Vector3D &direction, size_t lambda,
                                      size_t nbrMacroParticle, const Vector3D &color, double standardDeviation, int rng);
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

    /**
     * return a ptr at the element in the direction of the position, ie.
     * the element such that the vector position is between the start and the end.
     * But the vector position can be out of the element. If no element is
     * adequate, it will return a nullptr.
     */
    Element* elementFromPosition(Vector3D& position);


};

std::ostream& operator<<(std::ostream& os, const Accelerator &accelerator);


#endif //PARTICLEACCELERATOR_ACCELERATOR_H
