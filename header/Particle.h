/**
 * This header defines the Particle class.
 *
 * The main purpose of this class is to represent
 * anything that will move inside the accelerator
 * and has a mass, charge, position and momentum.
 *
 * Use the methods addMagneticForce and evolve to
 * actualize the force acting on the particle and
 * move it.
 *
 * --- Units ---
 * length : c * s
 * mass : GeV / c²
 * electric charge : e
 * energy : GeV
 * speed : c
 * momentum : GeV / c
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
    Vector3D position_;
    Vector3D momentum_;
    Vector3D force_;
    Element* element_;
    Vector3D color_;
public:
    /**
     * Create a new particle.
     * @param mass Mass in GeV/c²
     * @param charge Electric charge in eV
     * @param position Position in c*s
     * @param momentum Momentum in GeV/c
     * @param color The color of the particle
     */
    Particle(double mass, double charge, const Vector3D &position,
             const Vector3D &momentum, const Vector3D &color = Vector3D(1, 0, 0),
             Element* element = nullptr)
            : mass_(mass),
              charge_(charge),
              position_(position),
              momentum_(momentum),
              element_(element),
              color_(color)
    {}

    double charge() const { return charge_; }
    double mass() const { return mass_; }

    const Vector3D &momentum() const { return momentum_; }
    const Vector3D &position() const { return position_; }
    const Vector3D &color() const { return color_; }
    const Element* element() const { return element_; }

    /**
     * Speed vector of the particle. Unit: c
     * @return Speed vector
     */
    const Vector3D speed() const;
    /**
     * Velocity of the particle. Unit: c
     * @return Scalar velocity
     */
    double velocity() const { return sqrt(velocitySquared()); }
    /**
     * Velocity squared of the particle. Unit: c²
     * @return The scalar velocity of the particle but squared
     */
    double velocitySquared() const;
    /**
     * Return the norm squared of the component of the speed radial
     * relative to the ideal trajectory. Unit : c
     */
    double radialVelocitySqrd() const;
    /**
     * Return the norm squared of the radial distance of the particle
     * relative to the ideal trajectory. Unit : c * s
     */
    double radialDistanceSqrd() const;
    const Vector3D radialPosition() const { return element()->radialPosition(position()); }
    const Vector3D radialSpeed() const { return element()->radialSpeed(position(), speed()); }
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
     * Move the particle according to the forces acting on it
     * since the last call to evolve.
     * The `dt` should be the same as the one passed to each
     * `addMagneticForce`.
     *
     * @param dt Timestep for the integrator
     */
    void evolve(double dt);
    /**
     * If it collided or is out, it returns false.
     * Otherwise tt updates the element where the particle is
     * and returns true.
     */
    bool updateElement();
    /**
     * Energy of the particle. Unit : GeV
     */
    double energy() const;
    /**
     * Gamma of the particle. No unit.
     */
    double gamma() const;

    void draw(Support &support) const override { support.draw(*this); }
};


std::ostream& operator<<(std::ostream &os, const Particle &partic);

const Vector3D momentumFromSpeed(const Vector3D& speed, double mass);

#endif //PARTICLE_ACCELERATOR_PARTICLE_H
