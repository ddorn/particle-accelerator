//
// Created by diego on 3/18/19.
//

#include <iostream>
#include <QtSupport.h>

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
    view.translate(0, 0, -10);
    prog.setUniformValue("view", view);
    prog.setUniformValue("model", QMatrix4x4());
}

// Draw methods

void QtSupport::draw(const Particle &particle) {
    QMatrix4x4 model;
    Vector3D pos(particle.position());
    model.translate(pos.x(), pos.y(), pos.z());
    model.scale(0.03);
    drawSphere(model, particle.color());
//    drawVector(particle.speed(), particle.position());
}
void QtSupport::draw(const Element &element) {
    cout << element << endl;
}

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
void QtSupport::drawSphere(const QMatrix4x4 &model, double r, double g, double b) {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"

    prog.setUniformValue("view", view);
    prog.setUniformValue("model", model);
    prog.setAttributeValue(ColorId, r, g, b);

    sphere.draw(prog, VertexId);
}

void QtSupport::drawSphere(const QMatrix4x4 &model, const Vector3D &color) {
    drawSphere(model, color.x(), color.y(), color.z());
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

