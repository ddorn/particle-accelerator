//
// Created by diego on 3/18/19.
//

#ifndef PARTICLEACCELERATOR_QTSUPPORT_H
#define PARTICLEACCELERATOR_QTSUPPORT_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "Support.h"
#include "GlSphere.h"

class QtSupport : public Support {
private:
    QOpenGLShaderProgram prog;
    QMatrix4x4 view; // Camera
    GLSphere sphere;
public:
    // Initialisation
    // TODO: Why not put those two in the constructor ? Isn't it its purpose ?
    void init();
    void initPosition();

    // Draw objects
    void draw(const Particle &particle) override;
    void draw(const Element &element) override;
    void draw(const Vector3D &d) override;

    void drawCube(const QMatrix4x4 &model);
    void drawSphere(const QMatrix4x4 &model);

    // Set view
    void setProjection(const QMatrix4x4 &projection)
    { prog.setUniformValue("projection", projection); }

};


#endif //PARTICLEACCELERATOR_QTSUPPORT_H
