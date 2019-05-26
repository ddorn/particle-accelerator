/**
 * This header defines the Particle class.
 *
 * The main purpose of this class is to represent
 * anything that will move inside the accelerator
 * and has a mass, charge, position and momentum.
 *
 * Use the methods addMagneticForce, AddElectricForce and evolve to
 * actualize the force acting on the particle and
 * move it.
 *
 * --- Units ---
 * length : m
 * mass : GeV / c²
 * electric charge : C
 * energy : GeV
 * speed : m/s
 * momentum : kg * m / s
 */

#ifndef PARTICLE_ACCELERATOR_PARTICLE_H
#define PARTICLE_ACCELERATOR_PARTICLE_H

#include <cmath>
#include "Element.h"
#include "Vector3D.h"
#include "constants.h"
#include "Content.h"
#include "Support.h"

class Element;

class Particle : public Content {
private:
    double mass_;
    double charge_;
    size_t turns_ = 0;
    const Element* spawn_;  // Used to count number of turns
    Vector3D position_;
    RadialVec3D radialPosition_;
    RadialVec3D radialSpeed_;
    Vector3D force_;
    Vector3D lastForce_;
    Element *element_;
    Vector3D color_;
    Vector3D speed_;
    bool isAlive_;

    /**
     * This method is used at the creation of an instance, to obtain the speed from
     * the given momentum
     */
    double velocityFromEnergy(double energy, double mass) const;

public:
    /**
     * Create a new particle
     * @param mass the mass in GeV/c²
     * @param charge the charge in coulomb
     * @param energy the energy in GeV
     * @param position the position in meters
     * @param direction vector in the direction of the speed
     * @param color The color to represent the particle
     * @param element A c-like pointer to the element containing the particle
     */
    Particle(double mass, double charge, double energy, const Vector3D &position, const Vector3D &direction,
             Element *element, const Vector3D &color = Vector3D(1, 1, 1))
            : mass_(mass),
              charge_(charge),
              spawn_(element),
              position_(position),
              element_(element),
              color_(color),
              speed_(direction.isZero() ? Vector3D()
                                        : ~direction * velocityFromEnergy(energy, mass)) {
        if (element == nullptr) {
            std::cerr << "Particles SHALL spawn in elements" << std::endl;
            throw 1;
        }
        isAlive_ = true;
        radialPosition_ = element_->radialPosition(position_);
        radialSpeed_ = element_->radialSpeed(position_, speed_);

    }

    /**
     * Give the number of turns the particle has made in the accelerator since the
     * beginning of the simulation
     */
    size_t nbrOfTurns() const { return turns_; }

    /**
     * Return whether or not the particle turns in the clockwise direction.
     */
    bool clockwise() const { return Vector3D::e3.tripleProduct(position(), speed()) < 0; }
    double charge() const { return charge_; }

    /**
     * Give the mass in GeV / c²
     */
    double mass() const { return mass_; }

    /**
     * Give the mass in kg
     */
    double massSI() const { return mass() / constants::KG; }

    /**
     * Force applied during the last step
     */
    const Vector3D &lastForce() const { return lastForce_; }

    const Vector3D momentum() const { return massSI() * gamma() * speed(); }

    const Vector3D &position() const { return position_; }

    const Vector3D &color() const { return color_; }

    Element *element() const { return element_; }

    /**
     * Speed vector of the particle. Unit: m/s
     * @return Speed vector
     */
    const Vector3D &speed() const { return speed_; }

    /**
     * Velocity of the particle. Unit: m/s
     * @return Scalar velocity
     */
    double velocity() const { return speed().norm(); }

    /**
     * Velocity squared of the particle. Unit: m²/s²
     * @return The scalar velocity of the particle but squared
     */
    double velocitySquared() const { return speed().normSquared(); }

    const RadialVec3D radialPosition() const { return radialPosition_; }

    const RadialVec3D radialSpeed() const { return radialSpeed_; }

    /**
     * Give the longitudinal position in the accelerator
     */
    double longitudinalPosition() const { return element()->longitudinalPosition() + radialPosition().s(); }

    /**
     * Add a magnetic force on the particle that is applied
     * during a given timestep `dt`. This `dt` should be
     * consistent with the `dt` passed to evolve.
     *
     * @param b Magnetic field at the particle's position
     * @param dt Timestep during which the force applies.
     */
    void addMagneticForce(const Vector3D &b, double dt);
    /**
     * Add an electric force on the particle.
     * @param e Electric field at the particle's position
     */
    void addElectricForce(const Vector3D &e);
    /**
     * Apply the electric and magnetic interactions
     * between this particle and the particle given in
     * parameter. The forces are also applied on the
     * particle in parameter.
     * dt is the timestep. It should be consistent
     * with the dt passed to evolve.
     */
    void particleInteraction(Particle& p, double dt);
    /**
     * Add the force applied by the magnetic field
     * in the element wherein the particle is.
     */
    void addElementMagneticForce(double dt) { return addMagneticForce(element()->magneticForceAt(position()), dt); }
    /**
     * Give the magnetic field generated by the particle
     * at the position given in argument.
     */
    const Vector3D magneticFieldAt(const Vector3D &pos) const;
    /**
     * Give the electric field generated by the particle at
     * the position given in argument.
     */
    const Vector3D electricFieldAt(const Vector3D &pos) const;

    /**
     * Move the particle according to the forces acting on it
     * since the last call to evolve.
     * The `dt` should be the same as the one passed to each
     * `addMagneticForce`.
     *
     * @param dt Timestep for the integrator
     */
    void evolve(double dt);

    /**
     * If the is outside of the accelerator (aka dead), it returns false.
     * Otherwise it updates the element where the particle is
     * and returns true.
     */
    bool updateElement();

    /**
     * Energy of the particle. Unit : GeV
     */
    double energy() const { return gamma() * mass(); }

    /**
     * Gamma of the particle. No unit.
     */
    double gamma() const { return 1.0 / sqrt(1.0 - velocitySquared() / constants::LIGHT_SPEED_SQUARED); }

    void draw(Support &support) const override { support.draw(*this); }

    /**
     * Tell whether or not the particle is in the accelerator
     */
    bool isAlive() const { return isAlive_; }
};


std::ostream& operator<<(std::ostream &os, const Particle &partic);

#endif //PARTICLE_ACCELERATOR_PARTICLE_H
