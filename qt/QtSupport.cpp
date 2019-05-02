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
//    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);
    // Enable blending
    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);  // best
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sphere.initialize();
    initPosition();
}
void QtSupport::initPosition() {
    view.setToIdentity();
    view.translate(0, 0, -6);
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
    prog.setAttributeValue(ColorId, r, g, b, 1);

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
// Vector
void QtSupport::drawVector(Vector3D vec, const Vector3D &start) {
    vec += start;

    QMatrix4x4 model;
    prog.setUniformValue("model", model);
    prog.setUniformValue("view", view);

    glNormal3f(0, 2, 4);  // This is the lights position

    glBegin(GL_LINES);
    prog.setAttributeValue(VertexId, start.x(), start.y(), start.z());
    prog.setAttributeValue(VertexId, vec.x(), vec.y(), vec.z());
    glEnd();
}
// Tube
void QtSupport::drawTube(const QMatrix4x4 &model, double radius, const Vector3D &color) {
    prog.setUniformValue("model", model);
    prog.setUniformValue("view", view);

    prog.setAttributeValue(ColorId, color.x(), color.y(), color.z(), 0.5);

    constexpr int NB_CIRCLES(6);
    constexpr double X_STEP(1.0 / NB_CIRCLES);
    constexpr int NB_SEGMENTS(12);
    constexpr double ANGLE_STEP(2 * M_PI / NB_SEGMENTS);

    glBegin(GL_QUADS);
    glNormal3f(2, 2, 4);
    double x(0);
    for (int i(0); i < NB_CIRCLES; ++i) {
        double angle(0);
        for (int j = 0; j < NB_SEGMENTS; ++j) {
//            glNormal3f(0, radius * cos(angle), radius * sin(angle));
            prog.setAttributeValue(VertexId, x + X_STEP, radius * cos(angle), radius * sin(angle));
            prog.setAttributeValue(VertexId, x, radius * cos(angle), radius * sin(angle));
//            glNormal3f(0, radius * cos(angle + ANGLE_STEP), radius * sin(angle + ANGLE_STEP));
            prog.setAttributeValue(VertexId, x, radius * cos(angle + ANGLE_STEP), radius * sin(angle + ANGLE_STEP));
            prog.setAttributeValue(VertexId, x + X_STEP, radius * cos(angle + ANGLE_STEP), radius * sin(angle + ANGLE_STEP));
            angle += ANGLE_STEP;
        }
        x += X_STEP;
    }
    glEnd();
}
void QtSupport::drawTube(const Vector3D& start, const Vector3D &end, double radius, const Vector3D& color) {
    QMatrix4x4 model(posToModel(start, 1));
    Vector3D dir(~(end - start));
    double angle(acos(dir.x()));
    if (dir.y() < 0) angle *= -1;
    model.rotate(angle * 180 / M_PI, 0, 0, 1);

    drawTube(model, radius, color);
}


/********************************** Draw real objects **********************************/


void QtSupport::draw(const Vector3D &d) {
    drawVector(d);
}
void QtSupport::draw(const Particle &particle) {
    drawSphere(particle.position(), 0.03, particle.color());
}
void QtSupport::draw(const Accelerator &accelerator) {
    switch (viewMode) {
        case FREE:
            break;
        case FOLLOW_PARTICLE:
            if (!accelerator.beams().empty()) {
                const auto& b = accelerator.beams()[0];
                if (!b->macroParticles().empty()) {
                    const auto& particle = b->macroParticles()[0];
                    const Vector3D& pos(particle->position());
                    Vector3D look = pos + particle->speed();
                    view.setToIdentity();
//                    view.translate(particle->position().x(), particle->position().y(), particle->position().z());
                    view.lookAt(QVector3D(pos.x(), pos.y(), pos.z()),
                            QVector3D(look.x(), look.y(), look.z()),
                            QVector3D(0, 0, 1));
                } else {
                    initPosition();
                }
            } else {
                initPosition();
            }
            break;
    }

    prog.setUniformValue("view", view);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"

    for (const auto &e : accelerator.elements()) {  
        e->draw(*this);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT, GL_FILL);
    for (const auto& p : accelerator.beams()) {
        p->draw(*this);
    }
}
void QtSupport::draw(const Element &element) {
    // This just draw a cube at the start and end of the element
    drawCube(element.entree(), 0.05);
    drawCube(element.exit(), 0.05);
}
void QtSupport::draw(const StraightElement &element) {
    drawTube(element.entree(), element.exit(), element.radius(), Vector3D(0.2, 0.6, 1));
}
void QtSupport::draw(const Quadrupole &element  ) {
    drawTube(element.entree(), element.exit(), element.radius(), Vector3D(1, 0.7, 0));
}
void QtSupport::draw(const Segment &segment) {
    segment.StraightElement::draw(*this);
}
void QtSupport::draw(const CurvedElement &element) {
    Vector3D cc(element.centerOfCurvature());
    Vector3D relEntree(element.entree() - cc);
    Vector3D relExit(element.exit() - cc);

    QMatrix4x4 model;
    model.translate(cc.x(), cc.y());
    prog.setUniformValue("model", model);
    prog.setUniformValue("view", view);
    prog.setAttributeValue(ColorId, 1, 0, 0, 0.5);

    constexpr int NB_SEGMENTS(12);
    constexpr int NB_CIRCLES(6);
    constexpr double CIRCLE_ANGLE(2 * M_PI / NB_SEGMENTS);

    double a = acos(~relExit * ~relEntree);  // TODO: This supposes clockwise turn definition of accelerator
    double angle(a / NB_CIRCLES);


    glBegin(GL_QUADS);
    Vector3D center(relEntree);
    Vector3D axis1(relEntree ^ Vector3D::e3);
    for (int i = 0; i <= NB_CIRCLES ; ++i) {
        Vector3D next(relEntree.rotate(Vector3D::e3, -angle * i));
        Vector3D axis2(next ^ Vector3D::e3);
        Vector3D dir1(Vector3D::e3 * element.radius());
        Vector3D dir2(Vector3D::e3 * element.radius());
        for (int j = 0; j < NB_SEGMENTS; ++j) {
            Vector3D nextDir1(dir1.rotate(axis1, CIRCLE_ANGLE));
            Vector3D nextDir2(dir2.rotate(axis2, CIRCLE_ANGLE));

            Vector3D a1(center + dir1);
            Vector3D b1(center + nextDir1);
            Vector3D a2(next + dir2);
            Vector3D b2(next + nextDir2);

            prog.setAttributeValue(VertexId, a1.x(), a1.y(), a1.z());
            prog.setAttributeValue(VertexId, b1.x(), b1.y(), b1.z());
            prog.setAttributeValue(VertexId, b2.x(), b2.y(), b2.z());
            prog.setAttributeValue(VertexId, a2.x(), a2.y(), a2.z());

            dir1 = nextDir1;
            dir2 = nextDir2;
        }
        center = next;
        axis1 = axis2;
    }
    glEnd();
}
void QtSupport::draw(const Dipole &dipole) {
    dipole.CurvedElement::draw(*this);
}

void QtSupport::draw(const Beam &beam) {
    for (auto const& p : beam.macroParticles()) {
        draw(*p);
    }
}
QMatrix4x4 QtSupport::posToModel(const Vector3D &position, double scale) {
    QMatrix4x4 model;
    model.translate(position.x(), position.y(), position.z());
    model.scale(scale);
    return model;
}

void QtSupport::setViewMode(ViewMode v) {
    viewMode = v;
    if (viewMode == FREE) {
        initPosition();
    }
}

