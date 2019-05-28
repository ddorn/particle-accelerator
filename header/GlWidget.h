//
// Created by diego on 3/18/19.
//

#ifndef PARTICLEACCELERATOR_GLWIDGET_H
#define PARTICLEACCELERATOR_GLWIDGET_H


#include <QOpenGLWidget>     // Classe pour faire une fenêtre OpenGL
#include <QTime>             // Classe pour gérer le temps
#include "QtSupport.h"
#include "Content.h"
#include "Accelerator.h"
#include "Particle.h"
#include "constants.h"
#include "ScatterPlot.h"


class GlWidget : public QOpenGLWidget {
private:
    bool pause_ = false;
    double intensity = 0.5;
    int steps = 5;
    Accelerator accelerator;
    QtSupport support;
    ScatterPlot* scatterPlot;
public:
    GlWidget(Accelerator &accelerator, QWidget *parent = nullptr);

    virtual ~GlWidget() = default;

private:
    void addBeam(bool clockwise = true);
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
