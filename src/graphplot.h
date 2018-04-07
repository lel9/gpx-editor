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
    void updateHigh(const QModelIndex &topLeft,
                    const QModelIndex &bottomRight,
                    PointTableModel *model);
};

#endif // GRAPHPLOT_H
