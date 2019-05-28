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
//typedef std::unique_ptr<Node> LinkedList;

class Accelerator : public Content {
private:
    std::default_random_engine rng_;
    /**
     * Add a new particle in the accelerator.
     * @param particle Particle to add.
     */
    Vector3D start_;
    double length_;
    ElementVector elements_;
    BeamVector beams_;
    LinkedList particles_;
    static double MIN_DIST; // minimal distance for the application of the force between particles

    const Vector3D nextStart() const { return elements_.empty() ? start_ : elements_.back()->exit(); }
    void addElement(std::unique_ptr<Element>&& ptr);
public:
    explicit Accelerator(const Vector3D& start = Vector3D(), int rng = 42)
        : rng_(rng), start_(start), length_(0), particles_(std::make_unique<Node>()) {}
    Accelerator(const Accelerator &other) = delete;
    Accelerator(Accelerator &&other) = default;
    void operator=(const Accelerator & other) = delete;

    const LinkedList& particles() const { if (!particles_->isHead()) std::cout << 1; return particles_; }
    const ElementVector& elements() const { return elements_; }

    /**
     * Cleanup the dust in the Accelerator and remove all particles.
     */
    void cleanParticles() { particles_ = std::make_unique<Node>(); beams_.clear(); }
    /**
     * Remove all the elements of the accelerator.
     * Warning: don't forget to recycle all this metal otherwise students will have good reasons to demonstrate
     */
    void cleanElements() { elements_.clear(); length_ = 0; }

    /**
     * One small step for the accelerator, one giant leap for mankind.
     * Small is exactly 0.00000000001 seconds.
     */
    void evolve(double dt = 1e-11);

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
    bool addDipole(const Vector3D& exit, double radius, double curvature, double magneticFieldIntensity);
    /**
     * This method will create a dipole with the perfect magnetic field intensity, in function of
     * the mean mass, charge and energy of the particles. The particles must turn in the clockwise
     * direction. If it isn't the case, the charge must be the opposite of the charge of the
     * particles.
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

    /**
     * Add a circular beam.
     */
    bool addCircularBeam(double mass, double charge, double energy, const RadialVec3D &direction, size_t lambda,
                         size_t nbrMacroParticle, double standardDeviation = 1e-8);
    bool addCircularBeam(double mass, double charge, double energy, const RadialVec3D &direction, size_t lambda,
                         size_t nbrMacroParticle, double standardDeviation, int rng);

    bool addParticle(double mass, double charge, double energy, const Vector3D &position,
                     const Vector3D &direction);
    bool addParticle(const particle_ptr& particle);
    /**
    * @return if the last element ends where the first element begins.
    */
    bool isClosed() const;
    /**
     * Return whether the given position is inside an element of the accelerator
     */
    bool isInside(const Vector3D & position) const;
    double length() const { return length_; };
    void showElements(std::ostream& os) const;
    void showParticles(std::ostream& os) const;
    void showBeams(std::ostream& os) const;
private:

    /**
     * return a ptr at the element in the direction of the position, ie.
     * the element such that the vector position is between the start and the end.
     * But the vector position can be out of the element. If no element is
     * adequate, it will return a nullptr.
     */
    const Element* elementFromPosition(const Vector3D& position) const;

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

    void reorderParticleList() const;


};

std::ostream& operator<<(std::ostream& os, const Accelerator &accelerator);


#endif //PARTICLEACCELERATOR_ACCELERATOR_H
