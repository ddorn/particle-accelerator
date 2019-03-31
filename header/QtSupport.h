//
// Created by diego on 3/18/19.
//

#ifndef PARTICLEACCELERATOR_QTSUPPORT_H
#define PARTICLEACCELERATOR_QTSUPPORT_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "Support.h"
#include "GlSphere.h"
#include "all.h"

class QtSupport : public Support {
private:
    QOpenGLShaderProgram prog;
    QMatrix4x4 view; // Camera
    GLSphere sphere;
public:
    // Initialisation
    // TODO: Why not put those two in the constructor ? Isn't it its purpose ?
    // Answer: because it simply doesn't work... but why ?
    void init();
    void initPosition();

    // Draw objects


    void drawCube(const QMatrix4x4 &model);
    void drawSphere(const QMatrix4x4 &model, double r = 1, double g = 1, double b = 1);
    void drawSphere(const QMatrix4x4 &model, const Vector3D &color);
    void drawVector(Vector3D vec, const Vector3D &start = Vector3D());

    void draw(const Accelerator &accelerator) override;
    void draw(const CurvedElement &element) override;
    void draw(const Quadrupole &quadrupole) override;
    void draw(const StraightElement &element) override;
    void draw(const Vector3D &d) override;
    void draw(const Particle &particle) override;
    void draw(const Element &element) override;
    void draw(const Dipole &) override;;

    // Set view
    void setProjection(const QMatrix4x4 &projection)
    { prog.setUniformValue("projection", projection); }

    void translate(double x, double y, double z);

    void rotate(double angle, double dir_x, double dir_y, double dir_z);
};


#endif //PARTICLEACCELERATOR_QTSUPPORT_H
