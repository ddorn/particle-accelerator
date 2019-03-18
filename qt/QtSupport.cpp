//
// Created by diego on 3/18/19.
//

#include <iostream>
#include <QtSupport.h>

#include "QtSupport.h"
#include "vertex_shader.h"

using namespace std;

void QtSupport::draw(const Particle &particle) {
    QMatrix4x4 model;
    Vector3D pos(particle.position());
    model.translate(pos.x(), pos.y(), pos.z());
    model.scale(0.1);
    drawSphere(model);
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

void QtSupport::draw(const Element &element) {
    cout << element << endl;
}

void QtSupport::draw(const Vector3D &d) {
    cout << d << endl;
}

void QtSupport::drawSphere(const QMatrix4x4 &model) {
    prog.setUniformValue("view", view);
    prog.setUniformValue("model", model);
    prog.setAttributeValue(ColorId, 1, 1, 1);
    sphere.draw(prog, VertexId);
}
