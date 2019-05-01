//
// Created by diego on 3/18/19.
//

#include <QKeyEvent>
#include <GlWidget.h>

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
    accelerator.draw(support);
}

void GlWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    counter += 1;

//    if (stream && counter % 2 == 0)
//        accelerator.addParticle(M_PROTON, PROTON_CHARGE, Vector3D(1, 0, 0), Vector3D(1, 1, 0));

    //    double dt = chronometre.restart() / 1000.0;
    chronometre.restart();

    for (int i = 0; i < 1000; ++i) {
        accelerator.evolve(0.00001);
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
          accelerator.addCircularBeam(M_PROTON, PROTON_CHARGE, Vector3D(1, 0, 0), 1, 100, Vector3D(1, 0.2, 0.8));
//          accelerator.addParticle(M_PROTON, PROTON_CHARGE, Vector3D(1, 0, 0), Vector3D(1, 0, 0));
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
  };

  update(); // redessine
}

GlWidget::GlWidget(QWidget *parent)
        : QOpenGLWidget(parent), counter(0), accelerator(Vector3D(-2, 3, 0)) {

    build(intensity);
}

void GlWidget::build(double quadrupole_intensity) {
    double radius(0.2);
    Vector3D pqd(-1, 3, 0);
    Vector3D pd2(0, 3, 0);
    Vector3D pqf(1, 3, 0);
    Vector3D pd1(2, 3, 0);
    Vector3D pd(3, 2, 0);

    accelerator.cleanBeam();
    accelerator.cleanElements();
    for (int i = 0; i < 4; ++i) {
        accelerator.addQuadrupole(pqd, radius, quadrupole_intensity);
        accelerator.addSegment(pd2, radius);
        accelerator.addQuadrupole(pqf, radius, -quadrupole_intensity);
        accelerator.addSegment(pd1, radius);
        accelerator.addDipole(pd, radius, 1, 1);  // 5.89158);

        pqf = pqf ^ Vector3D::e3;
        pd1 = pd1 ^ Vector3D::e3;
        pd = pd ^ Vector3D::e3;
        pqd = pqd ^ Vector3D::e3;
        pd2 = pd2 ^ Vector3D::e3;
    }

    accelerator.addCircularBeam(M_PROTON, PROTON_CHARGE, Vector3D(1, 0, 0), 1, 100, Vector3D(1, 0.2, 0.8));
}




