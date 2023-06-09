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
    showFullScreen();
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
    const Color& color(support.theme()->bgColor());
    glClearColor(color.r(), color.g(), color.b(), 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // And then draw the accelerator
    support.draw(accelerator);
#ifdef USE_QT_CHARTS
    if (!scatterPlot->isHidden()) scatterPlot->update(accelerator.particles().get());
#endif
}

void GlWidget::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    //    double dt = chronometre.restart() / 1000.0;
    chronometre.restart();

    for (int i = 0; i < steps * !pause_; ++i) {
        accelerator.evolve(1e-11);
    }

    update();
}

void GlWidget::keyPressEvent(QKeyEvent *event) {
    bool isShift = event->modifiers() & Qt::Modifier::SHIFT;
    double factor(isShift ? 0.1 : 1);

    const double petit_angle(4.5 / factor); // en degrés
    const double petit_pas(1.0 * factor);

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
            support.setViewMode(FREE_VIEW);
            support.initPosition();
            break;
        case Qt::Key_P:
            addBeam(!isShift);
            break;
        case Qt::Key_Space:
            pause_ = !pause_;
            break;
        case Qt::Key_Plus:
            intensity *= 1 + 0.4 * factor;
            std::cout << intensity << std::endl;
            break;
        case Qt::Key_Minus:
            intensity /= 1 + 0.4 * factor;
            std::cout << intensity << std::endl;
            break;
        case Qt::Key_Backspace:
            accelerator.cleanParticles();
            break;
        case Qt::Key_Escape:
            if (isShift) support.saveView(accelerator);
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
        case Qt::Key_Backtab:
            support.nextTheme(-1);
            break;
        case Qt::Key_K:
            steps += isShift ? 10 : 1;
            break;
        case Qt::Key_J:
            steps -= isShift ? 10 : 1;
            if (steps < 0) steps = 0;
            break;
        case Qt::Key_F11:
            if (isFullScreen()) showNormal();
            else showFullScreen();
            break;
#ifdef USE_QT_CHARTS
        case Qt::Key_G:
            if (scatterPlot->isHidden()) scatterPlot->show();
            else scatterPlot->hide();
            break;
#endif
        default:
            return;
    }
    event->accept();
    update(); // redessine
}

GlWidget::GlWidget(Accelerator &accelerator, QWidget *parent)
        : QOpenGLWidget(parent), accelerator(std::move(accelerator)) {}

void GlWidget::addBeam(bool clockwise) {
    // ---- Parametrisation of the particles ----
    double mass(constants::M_PROTON);
    double charge(constants::C_PROTON);
    double energy(2);

    if (clockwise) accelerator.addCircularBeam(mass, charge, energy, RadialVec3D(0, 1, 0), 1000, 42, 0.01);
    else accelerator.addCircularBeam(mass, -charge, energy, RadialVec3D(0, -1, 0), 1000, 42, 0.01);
}


