//
// Created by diego on 3/18/19.
//

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
    dt *= 0;
    accelerator.evolve(dt);
    update();
}

