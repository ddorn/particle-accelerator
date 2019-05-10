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
    const Color& color(support.theme()->getBgColor());
    glClearColor(color.x(), color.y(), color.z(), 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // And then draw the accelerator
    support.draw(accelerator);
}

void GlWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    counter += 1;

    //    double dt = chronometre.restart() / 1000.0;
    chronometre.restart();

    for (int i = 0; i < steps * 10; ++i) {
        accelerator.evolve(1e-12);
//        if (accelerator.particles().empty()) std::cout << counter << std::endl;
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
          support.setViewMode(FREE_VIEW);
          break;
      case Qt::Key_1:
          support.setViewMode(FIRST_PERSON);
          break;
      case Qt::Key_2:
          support.setViewMode(THIRD_PERSON);
          break;
      case Qt::Key_3:
          support.setViewMode(TOP_VIEW);
          break;
      case Qt::Key_Tab:
          support.nextTheme();
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
        : QOpenGLWidget(parent), counter(0), accelerator(Vector3D(3, 2, 0)) {

    build(intensity);
}

void GlWidget::build(double coucou) {
    accelerator.cleanBeam();
    accelerator.cleanElements();
//    double quadrupoleIntensity(1.2);
    double dipoleIntensity(5.891582055618276);

    double radius(0.1);
    Vector3D pd(2, -3, 0);
    Vector3D pSex(3, 2 - coucou, 0);
    Vector3D pFODO(3, -2, 0);

    for (int i = 0; i < 4; ++i) {
        accelerator.addSextupole(pSex, radius, 0);
        accelerator.addFODO(pFODO, 0.5, radius, 1.2);
        accelerator.addDipole(pd, radius, 1, dipoleIntensity);

        pSex = pSex ^ Vector3D::e3;
        pFODO = pFODO ^ Vector3D::e3;
        pd = pd ^ Vector3D::e3;
    }



//    addBeam();
}

void GlWidget::addBeam() {
    // ---- Parametrisation of the particles ----
    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
//    Vector3D position2(2.99, 2, 0);
//    Particle p2(mass, charge, 2, position2, Vector3D(0, -1, 0), accelerator.elements()[18].get(), Vector3D(1, 1, 1));
//    Particle p0(mass, charge, 2, Vector3D(2.99, 0, 0), Vector3D(0, -1, 0), accelerator.elements()[0].get(), Vector3D(1, 1, 1));
    //  ---------
//    accelerator.addParticle(p0);

    accelerator.addCircularBeam(mass, -charge, 2, Vector3D(0, -1, 0), 1, 100);
}




