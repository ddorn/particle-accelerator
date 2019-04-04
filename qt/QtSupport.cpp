//
// Created by diego on 3/18/19.
//

#include <iostream>
#include <QtSupport.h>


#include "all.h"
#include "QtSupport.h"
#include "vertex_shader.h"

using namespace std;

// Initialisation

void QtSupport::init() {

    // We create a almost basic shader that can do a bit of lighting
    prog.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
    prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

    // And identify the vertex attributes for Qt
    // The vertex (id=0) is special and sends the new vertex to openGl
    // Therefore all attributes of the vertex should be sent before
    prog.bindAttributeLocation("vertex", VertexId);
    prog.bindAttributeLocation("color", ColorId);

    // Compile the shader
    if (!prog.link()) throw "Shader failed compilation";
    // And activate it
    if (!prog.bind()) throw "Unable to bind the shader";

    // We activate the depth test and backface culling for now, as we
    // do not want to draw faces that are hidden
    // This may change if we draw the Elements with transparency
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    sphere.initialize();
    initPosition();
}
void QtSupport::initPosition() {
    view.setToIdentity();
    view.translate(0, 0, -4);
    prog.setUniformValue("view", view);
    prog.setUniformValue("model", QMatrix4x4());
}

// Move view

void QtSupport::translate(double x, double y, double z) {
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  view = translation_supplementaire * view;
  prog.setUniformValue("view", view);
}
void QtSupport::rotate(double angle, double dir_x, double dir_y, double dir_z) {
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  view = rotation_supplementaire * view;
  prog.setUniformValue("view", view);
}


// Base draw methods
// Cube
void QtSupport::drawCube(const QMatrix4x4 &model = QMatrix4x4()) {

    prog.setUniformValue("view", view);
    prog.setUniformValue("model", model);

    glBegin(GL_QUADS);
    // face coté X = +1
    prog.setAttributeValue(ColorId, 1.0, 0.0, 0.0); // rouge
    glNormal3f(1, 0, 0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);

    // face coté X = -1
    prog.setAttributeValue(ColorId, 0.0, 1.0, 0.0); // vert
    glNormal3f(-1, 0, 0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);


    // face coté Y = +1
    prog.setAttributeValue(ColorId, 0.0, 0.0, 1.0); // bleu
    glNormal3f(0, 1, 0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);

    // face coté Y = -1
    prog.setAttributeValue(ColorId, 0.0, 1.0, 1.0); // cyan
    glNormal3f(0, -1, 0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);

    // face coté Z = +1
    prog.setAttributeValue(ColorId, 1.0, 1.0, 0.0); // jaune
    glNormal3f(0, 0, 1);
    prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);

    // face coté Z = -1
    prog.setAttributeValue(ColorId, 1.0, 0.0, 1.0); // magenta
    glNormal3f(0, 0, -1);
    prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);

    glEnd();
}
void QtSupport::drawCube(const Vector3D &position, double scale) {
    drawCube(posToModel(position, scale));
}
// Circle
void QtSupport::drawCircle(const QMatrix4x4 &model, double r, double g, double b, size_t points) {
    prog.setUniformValue("view", view);
    prog.setUniformValue("model", model);
    prog.setAttributeValue(ColorId, r, g, b);

    glBegin(GL_LINE_LOOP);  // draw closed lines
    glNormal3f(0, 2, 4);
    for (size_t p = 0; p < points; ++p) {
        double x(cos(M_PI * 2.0 * p / points));
        double y(sin(M_PI * 2.0 * p / points));
        prog.setAttributeValue(VertexId, x, y, 0);
    }
    glEnd();
}
void QtSupport::drawCircle(const Vector3D &position, double radius, const Vector3D &dir, const Vector3D &color) {
    QMatrix4x4 model;
    model.translate(position.x(), position.y(), position.z());

    prog.setUniformValue("view", view);
    prog.setUniformValue("model", model);
    prog.setAttributeValue(ColorId, color.x(), color.y(), color.z());

    // We calculate a vector orthogonal to radius. Either radius^e1 or radius^e2 is non zero
    Vector3D r(Vector3D::e1 ^ dir);
    if (r.isZero()) r = Vector3D::e2 ^ dir;
    r = ~r * radius;

    glBegin(GL_LINE_LOOP);  // draw closed lines
    glNormal3f(0, 2, 4);
    for (size_t p = 0; p < 30; ++p) {
        Vector3D v(r.rotate(dir, M_PI * 2 * p / 30.0));
        prog.setAttributeValue(VertexId, v.x(), v.y(), v.z());
    }
    glEnd();
}
// Sphere
void QtSupport::drawSphere(const QMatrix4x4 &model, double r, double g, double b) {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"

    prog.setUniformValue("view", view);
    prog.setUniformValue("model", model);
    prog.setAttributeValue(ColorId, r, g, b);

    sphere.draw(prog, VertexId);
}
void QtSupport::drawSphere(const QMatrix4x4 &model, const Vector3D &color)  {
    drawSphere(model, color.x(), color.y(), color.z());
}
void QtSupport::drawSphere(const Vector3D &position, double scale, const Vector3D &color) {
    drawSphere(position, scale, color.x(), color.y(), color.z());
}
void QtSupport::drawSphere(const Vector3D &position, double scale, double r, double g, double b) {
    drawSphere(posToModel(position, scale), r, g, b);
}
void QtSupport::drawVector(Vector3D vec, const Vector3D &start) {
    vec += start;

    QMatrix4x4 model;
    prog.setUniformValue("model", model);
    glNormal3f(0, 2, 4);  // This is the lights position

    glBegin(GL_LINES);
    prog.setAttributeValue(VertexId, start.x(), start.y(), start.z());
    prog.setAttributeValue(VertexId, vec.x(), vec.y(), vec.z());
    glEnd();
}

// Draw real objects

void QtSupport::draw(const Vector3D &d) {
    drawVector(d);
}
void QtSupport::draw(const Particle &particle) {
    drawSphere(particle.position(), 0.03, particle.color());
}
void QtSupport::draw(const Accelerator &accelerator) {
    for (const auto& p : accelerator.particles()) {
        p->draw(*this);
    }
    for (const auto &e : accelerator.elements()) {
        e->draw(*this);
    }
}
void QtSupport::draw(const Element &element) {
    // This just draw a cube at the start and end of the element
    drawCube(element.entree(), 0.05);
    drawCube(element.exit(), 0.05);
}
void QtSupport::draw(const StraightElement &element) {
    Vector3D axis(element.exit() - element.entree());
    constexpr double NB_CIRCLES(10);
    for (int i = 0; i < NB_CIRCLES; ++i) {
        Vector3D pos(element.exit() * (i / NB_CIRCLES) + element.entree() * (1 - i / NB_CIRCLES));
        drawCircle(pos, element.radius(), axis, Vector3D(0.2, 0.6, 1));
    }
}
void QtSupport::draw(const Quadrupole &element  ) {
    Vector3D axis(element.exit() - element.entree());
    constexpr double NB_CIRCLES(10);
    for (int i = 0; i < NB_CIRCLES; ++i) {
        Vector3D pos(element.exit() * (i / NB_CIRCLES) + element.entree() * (1 - i / NB_CIRCLES));
        drawCircle(pos, element.radius(), axis, Vector3D(1, 0.7, 0));
    }}
void QtSupport::draw(const Segment &segment) {
    segment.StraightElement::draw(*this);
}
void QtSupport::draw(const CurvedElement &element) {
    Vector3D cc(element.centerOfCurvature());
    Vector3D relEntree(element.entree() - cc);
    Vector3D relExit(element.exit() - cc);
    double angle(acos(relExit * relEntree));
    for (int i = 0; i < 10; ++i) {
        Vector3D pos(relEntree.rotate(Vector3D::e3, -angle * i / 10.0));
        Vector3D axis(pos ^ Vector3D::e3);
        drawCircle(pos + cc, element.radius(), axis, Vector3D(0.2, 0.6, 1));
    }
}
void QtSupport::draw(const Dipole &dipole) {
    dipole.CurvedElement::draw(*this);
}

QMatrix4x4 QtSupport::posToModel(const Vector3D &position, double scale) {
    QMatrix4x4 model;
    model.translate(position.x(), position.y(), position.z());
    model.scale(scale);
    return model;
}


