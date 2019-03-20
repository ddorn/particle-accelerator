//
// Created by diego on 3/18/19.
//

#include <QKeyEvent>

#include "GlWidget.h"

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
    accelerator.draw();
}

void GlWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    double dt = chronometre.restart() / 1000.0;
    accelerator.evolve(dt);
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
    support.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    support.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    support.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    support.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    support.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    support.translate(0.0,  petit_pas, 0.0);
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
  };

  update(); // redessine
}

