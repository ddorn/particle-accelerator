//
// Created by diego on 5/23/19.
//

#include "ScatterPlot.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QValueAxis>
#include <QtGui/QPainter>
#include <QtCore/QtMath>

using namespace constants;

ScatterPlot::ScatterPlot(QWidget *parent) : QChartView(new QChart(), parent), axisX(new QValueAxis), axisY(new QValueAxis), serie(new QScatterSeries) {
    setPlotMode(PlotMode::PHASE_SPACE_R);

    serie->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    serie->setMarkerSize(15.0);

    chart()->addAxis(axisX, Qt::AlignBottom);
    chart()->addAxis(axisY, Qt::AlignLeft);
    setRenderHint(QPainter::Antialiasing);

    chart()->setTitle("Simple scatterchart example");
    chart()->setDropShadowEnabled(false);

    chart()->addSeries(serie);
    serie->attachAxis(axisX);
    serie->attachAxis(axisY);

    //    chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);

}

void ScatterPlot::update(Node *particles) {
    serie->clear();

    for (auto& p : *particles) {
        Particle &particle(*p.particle());
        double x, y;
        switch (mode_) {
            case RADIAL_POSITION:
                x = particle.radialPosition().r();
                y = particle.radialPosition().z();
                break;
            case RADIAL_SPEED:
                x = particle.radialSpeed().r();
                y = particle.radialSpeed().z();
                break;
            case PHASE_SPACE_R:
                x = particle.radialPosition().r();
                y = particle.radialSpeed().r();
                break;
            case PHASE_SPACE_Z:
                x = particle.radialPosition().z();
                y = particle.radialSpeed().z();
                break;
            default:
                x = y = 0;
        }
        serie->append(x, y);
    }
}

void ScatterPlot::setPlotMode(PlotMode mode) {
    mode_ = mode;
    constexpr double VELOCITY_MAX = 1e7;
    switch (mode_) {
        case RADIAL_POSITION:
            axisY->setMin(-0.1);
            axisY->setMax(0.1);

            axisX->setMin(-0.1);
            axisX->setMax(0.1);
            break;
        case RADIAL_SPEED:
            axisY->setMin(-VELOCITY_MAX);
            axisY->setMax(VELOCITY_MAX);

            axisX->setMin(-VELOCITY_MAX);
            axisX->setMax(VELOCITY_MAX);
            break;
        case PHASE_SPACE_R:
            axisY->setMin(-VELOCITY_MAX);
            axisY->setMax(VELOCITY_MAX);

            axisX->setMin(-0.1);
            axisX->setMax(0.1);
            break;
        case PHASE_SPACE_Z:
            axisY->setMin(-VELOCITY_MAX);
            axisY->setMax(VELOCITY_MAX);

            axisX->setMin(-0.1);
            axisX->setMax(0.1);
            break;
    }
}

void ScatterPlot::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_1:
            setPlotMode(RADIAL_POSITION);
            break;
        case Qt::Key_2:
            setPlotMode(RADIAL_SPEED);
            break;
        case Qt::Key_3:
            setPlotMode(PHASE_SPACE_R);
            break;
        case Qt::Key_4:
            setPlotMode(PHASE_SPACE_Z);
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}
