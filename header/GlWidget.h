//
// Created by diego on 3/18/19.
//

#ifndef PARTICLEACCELERATOR_GLWIDGET_H
#define PARTICLEACCELERATOR_GLWIDGET_H


#include <random>
#include <QOpenGLWidget>     // Classe pour faire une fenêtre OpenGL
#include <QTime>             // Classe pour gérer le temps
#include "QtSupport.h"
#include "Content.h"
#include "Accelerator.h"
#include "Particle.h"
#include "constants.h"

using namespace constants;

class GlWidget : public QOpenGLWidget {
private:
    Accelerator accelerator;
    QtSupport support;
public:
    GlWidget(QWidget *parent = nullptr)
            : QOpenGLWidget(parent), accelerator(&support) {
        std::mt19937 rng(42);
        std::normal_distribution<double> normal_distribution(0, 1);

        for (int i = 0; i < 4200; ++i) {
            accelerator.add(Particle(M_PROTON, PROTON_CHARGE,
                                     Vector3D(normal_distribution(rng),
                                              normal_distribution(rng),
                                              0),
                                     Vector3D(0.8, 0, 0).rotate(Vector3D::e3, normal_distribution(rng))
            ));
        }

    }

    virtual ~GlWidget() = default;

private:
    // The 3 key methods of QOpenGLWidget to reimplement
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    // Events
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Timer
    int timerId;
    // pour faire évoluer les objets avec le bon "dt"
    QTime chronometre;
};


#endif //PARTICLEACCELERATOR_GLWIDGET_H
