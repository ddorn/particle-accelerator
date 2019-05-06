//
// Created by diego on 3/18/19.
//

#include <QKeyEvent>
#include <vector>
#include "Segment.h"
#include "GlWidget.h"
#include "Dipole.h"

// Methods needed by QOpenGLWidget
void GlWidget::initializeGL() {
    support.init();
    timerId = startTimer(1);
}
void GlWidget::resizeGL(int width, int height) {
    // For now we wnat to draw on the whole window
    glViewport(0, 0, width, height);

    // We modify the perspective and send it to the shader
    QMatrix4x4 matrice;
    matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
    support.setProjection(matrice);
}
void GlWidget::paintGL() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // And then draw the accelerator
    support.draw(accelerator);
}

void GlWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    counter += 1;

    //    double dt = chronometre.restart() / 1000.0;
    chronometre.restart();

    for (int i = 0; i < steps; ++i) {
        accelerator.evolve(1e-11);
        if (accelerator.beams().empty()) std::cout << counter << std::endl;
    }

    update();
}

void GlWidget::keyPressEvent(QKeyEvent *event) {

  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(1.0);

  switch (event->key()) {

      case Qt::Key_Left:
          support.rotate(petit_angle, 0.0, -1.0, 0.0);
          break;

      case Qt::Key_Right:
          support.rotate(petit_angle, 0.0, +1.0, 0.0);
          break;

      case Qt::Key_Up:
          support.rotate(petit_angle, -1.0, 0.0, 0.0);
          break;

      case Qt::Key_Down:
          support.rotate(petit_angle, +1.0, 0.0, 0.0);
          break;

      case Qt::Key_PageUp:
      case Qt::Key_W:
          support.translate(0.0, 0.0, petit_pas);
          break;

      case Qt::Key_PageDown:
      case Qt::Key_S:
          support.translate(0.0, 0.0, -petit_pas);
          break;

      case Qt::Key_A:
          support.translate(petit_pas, 0.0, 0.0);
          break;

      case Qt::Key_D:
          support.translate(-petit_pas, 0.0, 0.0);
          break;

      case Qt::Key_R:
          support.translate(0.0, -petit_pas, 0.0);
          break;

      case Qt::Key_F:
          support.translate(0.0, petit_pas, 0.0);
          break;

      case Qt::Key_Q:
          support.rotate(petit_angle, 0.0, 0.0, -1.0);
          break;

      case Qt::Key_E:
          support.rotate(petit_angle, 0.0, 0.0, +1.0);
          break;

      case Qt::Key_Home:
          support.initPosition();
          break;
      case Qt::Key_P:
          addBeam();
//          accelerator.addCircularBeam(M_PROTON, C_PROTON, Vector3D(1, 0, 0), 1, 100);
//          accelerator.addParticle(M_PROTON, C_PROTON, Vector3D(1, 0, 0), Vector3D(1, 0, 0));
          break;
      case Qt::Key_Space:
          stream = !stream;
          break;
      case Qt::Key_Plus:
          intensity *= 1.05;
          std::cout << intensity << std::endl;
          build(intensity);
          break;
      case Qt::Key_Minus:
          intensity /= 1.05;
          std::cout << intensity << std::endl;
          build(intensity);
          break;
      case Qt::Key_Backspace:
          accelerator.cleanBeam();
          break;
      case Qt::Key_Escape:
          support.setViewMode(FREE);
          break;
      case Qt::Key_1:
          support.setViewMode(FOLLOW_PARTICLE);
          break;
      case Qt::Key_K:
          steps += 5;
          break;
      case Qt::Key_J:
          steps -= 1;
          if (steps < 1) steps = 1;
          break;
  };

  update(); // redessine
}

GlWidget::GlWidget(QWidget *parent)
        : QOpenGLWidget(parent), counter(0), accelerator(Vector3D(3, 0, 0)) {

    build(intensity);
}

void GlWidget::build(double) {

    double quadrupoleIntensity(1.2);
    double dipoleIntensity(5.891582055618276);

    double radius(0.1);
    Vector3D pqf(3, -1, 0);
    Vector3D pd1(3, -2, 0);
    Vector3D pd(2, -3, 0);
    Vector3D pqd(1, -3, 0);
    Vector3D pd2(0, -3, 0);

    for (int i = 0; i < 4; ++i) {
        accelerator.addQuadrupole(pqf, radius, -quadrupoleIntensity);
        accelerator.addSegment(pd1, radius);
        accelerator.addDipole(pd, radius, 1, dipoleIntensity);
        accelerator.addQuadrupole(pqd, radius, quadrupoleIntensity);
        accelerator.addSegment(pd2, radius);

        pqf = pqf ^ Vector3D::e3;
        pd1 = pd1 ^ Vector3D::e3;
        pd = pd ^ Vector3D::e3;
        pqd = pqd ^ Vector3D::e3;
        pd2 = pd2 ^ Vector3D::e3;
    }

//
//    double radius(0.1);
//    Vector3D pqd(-1, 3, 0);
//    Vector3D pd2(0, 3, 0);
//    Vector3D pqf(1, 3, 0);
//    Vector3D pd1(2, 3, 0);
//    Vector3D pd(3, 2, 0);
//
//    quadrupole_intensity = -1.2;
//
//    accelerator.cleanBeam();
//    accelerator.cleanElements();
//    for (int i = 0; i < 4; ++i) {
//        accelerator.addQuadrupole(pqd, radius, quadrupole_intensity);
//        accelerator.addSegment(pd2, radius);
//        accelerator.addQuadrupole(pqf, radius, -quadrupole_intensity);
//        accelerator.addSegment(pd1, radius);
//        accelerator.addDipole(pd, radius, 1, 5.891582055618276);
//
//        pqf = pqf ^ Vector3D::e3;
//        pd1 = pd1 ^ Vector3D::e3;
//        pd = pd ^ Vector3D::e3;
//        pqd = pqd ^ Vector3D::e3;
//        pd2 = pd2 ^ Vector3D::e3;
//    }
//
////    accelerator.addCircularBeam(M_PROTON, C_PROTON, Vector3D(1, 0, 0), 1, 100, Vector3D(1, 0.2, 0.8));
    addBeam();
}

void GlWidget::addBeam() {
    // ---- Parametrisation of the particles ----
    Vector3D speed(0, -264754494.1719916, 0); // constants::LIGHT_SPEED_MS);
    double gamma(2.131578049861873);
    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    Vector3D momentum(speed * gamma * mass / constants::KG);
    Vector3D position1(3.01, 0, 0);
    Vector3D position2(2.99, 0, 0);
    Particle p1(mass, charge, position1, momentum);
    Particle p2(mass, charge, position2, momentum);
    std::vector<Particle> particles{p2};
    accelerator.addBeam(mass, charge,
                        momentum, 1, particles);

    //  ---------

//
//    Vector3D speed(264754494.1719916, 0, 0); // constants::LIGHT_SPEED_MS);
//    double gamma(2.131578049861873);
//    double mass(constants::M_PROTON);
//    double charge(constants::C_PROTON);
//    Vector3D momentum(speed * gamma * mass / constants::KG);
//    Vector3D position1(3.01, 0, 0);
//    Vector3D position2(-2, 2.99, 0);
//    Particle p1(mass, charge, position1, momentum);
//    Particle p2(mass, charge, position2, momentum);
//    std::vector<Particle> particles{p2};
//    accelerator.addBeam(mass, charge,
//                       momentum, 1, particles);

//    Vector3D speed(264754494.1719916, 0, 0); // constants::LIGHT_SPEED_MS);
//    double gamma(2.131578049861873);
//    double mass(constants::M_PROTON);
//    Vector3D momentum(speed * gamma * mass / KG);
//    accelerator.addCircularBeam(M_PROTON, C_PROTON, momentum, 1, 100);
}




