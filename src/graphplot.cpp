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

GraphPlot &GraphPlot::operator=(const GraphPlot &other)
{
    for (int i = 0; i < other.graphCount(); i++)
    {
        addGraph();
        mGraphs[i]->setData(other.mGraphs[i]->data());
    }
    return *this;
}

bool operator==(const GraphPlot &first, const GraphPlot &second)
{
    if (first.graphCount() != second.graphCount())
        return false;

    for (int i = 0; i < first.graphCount(); i++)
    {
        int len1 = first.mGraphs[i]->data()->values().length();
        int len2 = second.mGraphs[i]->data()->values().length();

        if (len1 != len2)
            return false;

        for (int i = 0; i < len1; i++)
        {
            if (first.mGraphs[i]->data()->values()[i].key != second.mGraphs[i]->data()->values()[i].key)
                return false;
            if (first.mGraphs[i]->data()->values()[i].value != second.mGraphs[i]->data()->values()[i].value)
                return false;
        }
    }

    return true;
}

bool operator!=(const GraphPlot &first, const GraphPlot &second)
{
    return (first == second);
}

