//
// Created by diego on 5/23/19.
//

#ifndef PARTICLEACCELERATOR_SCATTERPLOT_H
#define PARTICLEACCELERATOR_SCATTERPLOT_H

#include <QtCharts/QChartView>
#include <QValueAxis>
#include <QtCharts/QScatterSeries>
#include "Node.h"

QT_CHARTS_USE_NAMESPACE

enum PlotMode {
    RADIAL_POSITION,
    RADIAL_SPEED,
    PHASE_SPACE_R,
    PHASE_SPACE_Z
};

class ScatterPlot : public QChartView {
private:
    PlotMode mode_;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QScatterSeries* serie;
public:
    explicit ScatterPlot(QWidget *parent = nullptr);
    void update(Node* particles);
    void setPlotMode(PlotMode mode);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif //PARTICLEACCELERATOR_SCATTERPLOT_H
