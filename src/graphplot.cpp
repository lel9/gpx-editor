#include "graphplot.h"

GraphPlot::GraphPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    graph = this->addGraph();
    graph->setName("Карта высот");
    xAxis->setLabel("Пройденное расстояние, км");
    yAxis->setLabel("Высота, м");
}

GraphPlot::GraphPlot(const GraphPlot &other) :
    QCustomPlot()
{
    graph = this->addGraph();
    graph->setName(other.graph->name());
    xAxis->setLabel(other.xAxis->label());
    yAxis->setLabel(other.yAxis->label());
    graph->setData(other.graph->data(), true);
}

void GraphPlot::setPlotData(const QVector<double> &keys, const QVector<double> &values)
{
    graph->setData(keys, values);
    rescaleAxes();
    replot();
}

QVector<double> GraphPlot::keys() const
{
    QVector<double> res;
    for (int i = 0; i < graph->data()->values().length(); i++)
        res << graph->data()->values()[i].key;
    return res;
}

QVector<double> GraphPlot::values() const
{
    QVector<double> res;
    for (int i = 0; i < graph->data()->values().length(); i++)
        res << graph->data()->values()[i].value;
    return res;
}

GraphPlot &GraphPlot::operator=(const GraphPlot &other)
{
    this->clearGraphs();

    graph = this->addGraph();
    graph->setName(other.graph->name());
    xAxis->setLabel(other.xAxis->label());
    yAxis->setLabel(other.yAxis->label());
    graph->setData(other.graph->data(), true);
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

