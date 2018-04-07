#include "graphplot.h"

GraphPlot::GraphPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    graph = this->addGraph();
    graph->setName("Карта высот");
    xAxis->setLabel("Пройденное расстояние, км");
    yAxis->setLabel("Высота, м");
}

void GraphPlot::updateHigh(const QModelIndex &topLeft,
                           const QModelIndex &bottomRight,
                           PointTableModel *model)
{
    Q_UNUSED(topLeft)
    Q_UNUSED(bottomRight)

    int endRow = model->rowCount();
    if (endRow == 0)
        graph->clearData();
    else
    {
        int beginRow = 0;
        double distance = 0;
        QGeoCoordinate lastPoint = model->pointAt(beginRow);
        QVector<double> alt, dist;
        for (int i = beginRow; i < endRow; i++)
        {
            QGeoCoordinate point = model->pointAt(i);
            alt << point.altitude();
            distance += lastPoint.distanceTo(point) / 1000.;
            dist << distance;
            lastPoint = point;
        }
        graph->setData(dist, alt);
    }
    rescaleAxes();
    replot();
}

