#ifndef GRAPHPLOT_H
#define GRAPHPLOT_H

#include "qcustomplot/qcustomplot.h"
#include "point_table_model.h"

class GraphPlot : public QCustomPlot
{
private:
    QCPGraph *graph;
public:
    GraphPlot(QWidget *parent = 0);
    GraphPlot(const GraphPlot &other);

    void setPlotData(const QVector<double> &keys, const QVector<double> &values);
    QVector<double> keys() const;
    QVector<double> values() const;

    GraphPlot& operator=(const GraphPlot &other);

    // для тестов
    friend bool operator==(const GraphPlot &first, const GraphPlot &second);
    friend bool operator!=(const GraphPlot &first, const GraphPlot &second);
};

#endif // GRAPHPLOT_H
