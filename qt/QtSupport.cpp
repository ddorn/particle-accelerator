//
// Created by diego on 3/18/19.
//

#include <iostream>
#include <QGLContext>
#include "all.h"
#include "QtSupport.h"
#include "vertex_shader.h"

using namespace std;


// Initialisation

void QtSupport::init() {
    initializeOpenGLFunctions();

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

    // Préparation d'une première texture à partir d'une image (cat.jpeg).
    auto* context =  const_cast<QGLContext*>(QGLContext::currentContext());
    epflTexture = context->bindTexture(QPixmap(":/epfl.png"), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

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
    glLineWidth(2);  // The size doesn't matter, but the width definitely does.

    sphere.initialize();
    initPosition();

    initThemes();
}

void QtSupport::initPosition() {
    position *= 0;
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
    position += Vector3D(x, y, z);
}

void QtSupport::rotate(double angle, double dir_x, double dir_y, double dir_z) {
    // Multiplie la matrice de vue par LA GAUCHE
    QMatrix4x4 rotation_supplementaire;
    rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
    view = rotation_supplementaire * view;
    prog.setUniformValue("view", view);
}

QMatrix4x4 QtSupport::lookAt(const Vector3D &eyePosition, const Vector3D &center, const Vector3D &up) {
    QMatrix4x4 m;
    m.lookAt(
            QVector3D(eyePosition.x(), eyePosition.y(), eyePosition.z()),
            QVector3D(center.x(), center.y(), center.z()),
            QVector3D(up.x(), up.y(), up.z())
    );
    return m;
}

const QMatrix4x4 QtSupport::updateViewMatrix(const Accelerator &accelerator) {
    Vector3D pos, speed;
    if (accelerator.particles()->empty()) {
        setViewMode(FREE_VIEW);
        followedParticle = nullptr;
    } else {
        if (followedParticle == nullptr or !followedParticle->isAlive()) {
            followedParticle = accelerator.particles()->next()->particle();
        }
        pos = followedParticle->position();
        speed = followedParticle->speed();
    }

    // We update whether we are inside the accelerator
    QVector3D p(view.inverted() * QVector3D());
    position = Vector3D(p.x(), p.y(), p.z());
    Element *element = accelerator.elementFromPosition(position);
    viewInsideAccelerator_ = viewMode == FIRST_PERSON
                             || viewMode == THIRD_PERSON
                             || (element != nullptr
                                 && !element->collideBorder(position));


    // We use the current view matrix only in free mode, otherwise
    // we determine it but don't save it so we can go back to where
    // we were looking before going in say, FPS
    QMatrix4x4 v;
    switch (viewMode) {
        case FREE_VIEW:
            v = view;
            break;
        case FIRST_PERSON:
            v = lookAt(pos, pos + speed, Vector3D::e3);
            break;
        case THIRD_PERSON:
            v = lookAt(pos - ~speed * 0.15, pos, Vector3D::e3);
            break;
        case TOP_VIEW:
            v = lookAt(pos + Vector3D::e3, pos, Vector3D::e3 ^ speed);
            break;
    }

    prog.setUniformValue("view", v);
    return v;
}

// Base draw methods
// Cube
void QtSupport::drawCube(const QMatrix4x4 &model = QMatrix4x4()) {

    prog.setUniformValue("model", model);

    glBegin(GL_QUADS);
    // face coté X = +1
    sendColor(1, 0, 0);
    glNormal3f(1, 0, 0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);

    // face coté X = -1
    sendColor(0, 1, 0);
    glNormal3f(-1, 0, 0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);


    // face coté Y = +1
    sendColor(0, 0, 1);
    glNormal3f(0, 1, 0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);

    // face coté Y = -1
    sendColor(0, 1, 1);
    glNormal3f(0, -1, 0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);

    // face coté Z = +1
    sendColor(1, 1, 0);
    glNormal3f(0, 0, 1);
    prog.setAttributeValue(VertexId, -1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, +1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, +1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, +1.0);

    // face coté Z = -1
    sendColor(1, 0, 1);
    glNormal3f(0, 0, -1);
    prog.setAttributeValue(VertexId, -1.0, -1.0, -1.0);
    prog.setAttributeValue(VertexId, -1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, +1.0, -1.0);
    prog.setAttributeValue(VertexId, +1.0, -1.0, -1.0);

    glEnd();
}

void QtSupport::drawCube(const Vector3D &pos, double scale) {
    drawCube(posToModel(pos, scale));
}

// Circle
void QtSupport::drawCircle(const QMatrix4x4 &model, double r, double g, double b, size_t points) {
    prog.setUniformValue("model", model);
    sendColor(r, g, b);

    glBegin(GL_LINE_LOOP);  // draw closed lines
    glNormal3f(0, 2, 4);
    for (size_t p = 0; p < points; ++p) {
        double x(cos(M_PI * 2.0 * p / points));
        double y(sin(M_PI * 2.0 * p / points));
        prog.setAttributeValue(VertexId, x, y, 0);
    }
    glEnd();
}

void QtSupport::drawCircle(const Vector3D &pos, double radius, const Vector3D &dir, const Color &color) {
    QMatrix4x4 model;
    model.translate(pos.x(), pos.y(), pos.z());

    prog.setUniformValue("model", model);
    sendColor(color);

    // We calculate a vector orthogonal to radius. Either radius^e1 or radius^e2 is non zero
    Vector3D r(Vector3D::e1 ^ dir);
    if (r.isZero()) r = Vector3D::e2 ^ dir;
    r = ~r * radius;

    glBegin(GL_LINE_LOOP);  // draw closed lines
    glNormal3f(0, 2, 4);
    for (size_t p = 0; p < 30; ++p) {
        sendPoint(r.rotate(dir, M_PI * 2 * p / 30.0));
    }
    glEnd();
}

// Sphere
void QtSupport::drawSphere(const QMatrix4x4 &model, const Color& color) {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // passe en mode "fil de fer"

    prog.setUniformValue("model", model);
    sendColor(color);
    /// Attribut la texture 'textureDeChat' à la texture numéro 0 du shader
    prog.setUniformValue("textureId", 0);
    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, epflTexture);

    sphere.draw(prog, VertexId);
}

void QtSupport::drawSphere(const Vector3D &pos, double scale, const Color &color) {
    drawSphere(posToModel(pos, scale), color);
}


// Vector
void QtSupport::drawVector(const Vector3D &vec, const Vector3D &start) {

    prog.setUniformValue("model", QMatrix4x4());
    sendColor(1, 1, 1);

    glBegin(GL_LINES);
    sendNormal();  // This is the lights position
    sendPoint(start);
    sendPoint(vec + start);
    glEnd();
}

// Tube
void QtSupport::drawTube(const Vector3D &start, const Vector3D &end, double radius, const Color &color) {
    // This supposes start and end are in the XY plane.

    Vector3D dir(~(end - start));
    double angle(acos(dir.x()));
    if (dir.y() < 0) angle *= -1;

    QMatrix4x4 model(posToModel(start, 1));
    model.rotate(angle * 180 / M_PI, 0, 0, 1);
    prog.setUniformValue("model", model);
    sendColor(color);

    const double length((end - start).norm());
    const int NB_CIRCLES(ceil(length / 0.2));
    const double X_STEP(length / NB_CIRCLES);
    constexpr int NB_SEGMENTS(8);
    constexpr double ANGLE_STEP(2 * M_PI / NB_SEGMENTS);

    glBegin(GL_QUADS);
    if (!elementsLighting()) sendNormal();

    double x(0);
    for (int i(0); i < NB_CIRCLES; ++i) {
        double a(0);
        for (int j(0); j < NB_SEGMENTS; ++j) {

            if (elementsLighting()) {
                // If tubes are not filled we should not apply lightning, as half of them are almost invisible
                Vector3D normal(0, radius * cos(a), radius * sin(a));
                normal = normal.rotate(Vector3D::e3, angle);
                sendNormal(normal);
            }

            prog.setAttributeValue(VertexId, x + X_STEP, radius * cos(a), radius * sin(a));
            prog.setAttributeValue(VertexId, x, radius * cos(a), radius * sin(a));

            if (elementsLighting()) {
                Vector3D normal(0, radius * cos(a + ANGLE_STEP), radius * sin(a + ANGLE_STEP));
                normal = normal.rotate(Vector3D::e3, angle);
                sendNormal(normal);
            }

            prog.setAttributeValue(VertexId, x, radius * cos(a + ANGLE_STEP), radius * sin(a + ANGLE_STEP));
            prog.setAttributeValue(VertexId, x + X_STEP, radius * cos(a + ANGLE_STEP), radius * sin(a + ANGLE_STEP));
            a += ANGLE_STEP;
        }
        x += X_STEP;
    }
    glEnd();
}

// Curved Tube
void QtSupport::drawCurvedTube(const Vector3D &start, const Vector3D &end, const Vector3D &center, double radius,
                               const Color &color) {

    Vector3D relEntree(start - center);
    Vector3D relExit(end - center);

    QMatrix4x4 model;
    model.translate(center.x(), center.y());

    prog.setUniformValue("model", model);
    sendColor(color);


    constexpr int NB_SEGMENTS(8);
    constexpr int NB_CIRCLES(6);
    constexpr double CIRCLE_ANGLE(2 * M_PI / NB_SEGMENTS);

    double a = acos(~relExit * ~relEntree);  // TODO: This supposes clockwise turn definition of accelerator
    double angle(a / NB_CIRCLES);


    glBegin(GL_QUADS);
    if (!elementsLighting()) sendNormal();

    Vector3D c(relEntree);
    Vector3D axis1(relEntree ^ Vector3D::e3);
    for (int i = 0; i <= NB_CIRCLES; ++i) {
        Vector3D next(relEntree.rotate(Vector3D::e3, -angle * i));
        Vector3D axis2(next ^ Vector3D::e3);
        Vector3D dir1(Vector3D::e3 * radius);
        Vector3D dir2(Vector3D::e3 * radius);
        for (int j = 0; j < NB_SEGMENTS; ++j) {
            Vector3D nextDir1(dir1.rotate(axis1, CIRCLE_ANGLE));
            Vector3D nextDir2(dir2.rotate(axis2, CIRCLE_ANGLE));

            if (elementsLighting()) sendNormal(dir1);
            sendPoint(c + dir1);
            if (elementsLighting()) sendNormal(nextDir1);
            sendPoint(c + nextDir1);
            if (elementsLighting()) sendNormal(nextDir2);
            sendPoint(next + nextDir2);
            if (elementsLighting()) sendNormal(dir2);
            sendPoint(next + dir2);

            dir1 = nextDir1;
            dir2 = nextDir2;
        }
        c = next;
        axis1 = axis2;
    }
    glEnd();

}


/********************************** Draw real objects **********************************/


void QtSupport::draw(const Vector3D &d) {
    drawVector(d);
}

void QtSupport::draw(const Particle &particle) {
    drawSphere(particle.position(), viewInsideAccelerator() ? 0.005 : 0.03, theme()->particleColor());
}

void QtSupport::draw(const Accelerator &accelerator) {
    updateViewMatrix(accelerator);

    if (viewInsideAccelerator()) {
        // When we are inside the accelerator, draw elements first
        // and then particles on top
        drawElements(accelerator);
        drawParticles(accelerator);
    } else {
        // We are probably outside (we could have a real check for collision but... no
        // So elements are on top of particles (so we don't need to sort fragments and
        // still have a good transparency
        drawParticles(accelerator);
        drawElements(accelerator);
    }
}

void QtSupport::draw(const Element &element) {
    // This just draw a cube at the start and end of the element
    drawCube(element.start(), 0.05);
    drawCube(element.exit(), 0.05);
}

void QtSupport::draw(const StraightElement &/*element*/) {
//    drawVector(element.exit() - element.start(), element.start());
}

void QtSupport::draw(const Quadrupole &element) {
    element.StraightElement::draw(*this);
    drawTube(element.start(), element.exit(), element.radius(), theme()->quadrupoleColor());
}

void QtSupport::draw(const Segment &element) {
    element.StraightElement::draw(*this);
    drawTube(element.start(), element.exit(), element.radius(), theme()->segmentColor());
}

void QtSupport::draw(const CurvedElement &/*element*/) {
//    drawCircle(element.centerOfCurvature(), 1 / element.curvature(), Vector3D::e3, Vector3D(1, 1, 1));
}

void QtSupport::draw(const Dipole &element) {
    element.CurvedElement::draw(*this);
    drawCurvedTube(element.start(), element.exit(), element.centerOfCurvature(), element.radius(),
                   theme()->dipoleColor());
}

void QtSupport::draw(const Sextupole &element) {
    element.StraightElement::draw(*this);
    drawTube(element.start(), element.exit(), element.radius(), theme()->sextupoleColor());

}

void QtSupport::draw(const Beam &beam) {
    for (auto const &p : beam.macroParticles()) {
        draw(*p);
    }
}


void QtSupport::drawParticles(const Accelerator &accelerator) {
    // We can never see through particles
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    if (theme()->isParticleFilled())glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


//    for (const auto &p : accelerator.beams()) {
//        p->draw(*this);
//    }
    int i(0);
    for (const auto &p : *accelerator.particles()) {
        sendColor(Color(5 * i % 360, 1.0, 1.0));
        p.particle()->draw(*this);
        ++i;
    }
}

void QtSupport::drawElements(const Accelerator &accelerator) {
    // We don't want the depth test because we want to see through the transparent faces
    glDisable(GL_DEPTH_TEST);
    // We want the back quads to be visible
    glDisable(GL_CULL_FACE);
    // Bigger lines = more visible
    glLineWidth(2);

    if (theme()->isElementFilled()) {
        // Draw the front and back side of quads as filled
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if (viewInsideAccelerator()) {
            // But not the backface when we are inside the accelerator
            // soo we can better see through
            glPolygonMode(GL_BACK, GL_LINE);
        } else {
            // Outside the accelerator we enable them because it's the easiest way to
            // remove drawing artifacts and have something consistent
            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
        }

    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        if (!viewInsideAccelerator()) {
            // Lines are a bit to big in top view so we make them smaller
            glLineWidth(1);
        }
    }

    // Activate transparency if needed
    if (theme()->segmentColor().a() != 1) glEnable(GL_BLEND);
    else glDisable(GL_BLEND);

    for (const auto &e : accelerator.elements()) {
        e->draw(*this);
    }
}

QMatrix4x4 QtSupport::posToModel(const Vector3D &pos, double scale) {
    QMatrix4x4 model;
    model.translate(pos.x(), pos.y(), pos.z());
    model.scale(scale);
    return model;
}

void QtSupport::initThemes() {
    themes.clear();
    themes.push_back(make_unique<Theme>(Theme::Classix()));
    themes.push_back(make_unique<Theme>(Theme::Matrix()));
    themes.push_back(make_unique<Theme>(Theme::EPFL()));
    themes.push_back(make_unique<Theme>(Theme::Pinx()));
    themes.push_back(make_unique<Theme>(Theme::Zloopix()));
    themes.push_back(make_unique<Theme>(Theme::RouteArcEnCiel()));
    themes.push_back(make_unique<Theme>(Theme::CurseOfDarkRainbow()));
    themes.push_back(make_unique<Theme>(Theme::Classix(false)));
}

void QtSupport::nextTheme(int n) {
    // size_t arithmetic apparently works differently...
    n %= (int) themes.size();
    //  So it's always positive
    if (n < 0) n += themes.size();
    themeIndex += n;
    themeIndex %= themes.size();
}

QtSupport::~QtSupport() {
    QGLContext* context =  const_cast<QGLContext*>(QGLContext::currentContext());
    context->deleteTexture(epflTexture);
}





