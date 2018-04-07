#include "testview.h"

TestView::TestView(QWidget *parent) :
    BaseView(parent)
{
    _routeView = new TableWidget;
    _pointView = new TableWidget;
    _graphPlot = new GraphPlot;
    _polylineEdit = new QTextEdit;
}

TestView::TestView(const TestView &other)
{
    *_routeView = *(other._routeView);
    *_pointView = *(other._pointView);
    *_graphPlot = *(other._graphPlot);
    _polylineEdit->setText(other._polylineEdit->toPlainText());
}

TestView::~TestView()
{
    delete _routeView;
    delete _pointView;
    delete _graphPlot;
    delete _polylineEdit;
}

TableWidget *TestView::routeView() const
{
    return _routeView;
}

TableWidget *TestView::pointView() const
{
    return _pointView;
}

GraphPlot *TestView::graphPlot() const
{
    return _graphPlot;
}

QTextEdit *TestView::polylineEdit() const
{
    return _polylineEdit;
}

QModelIndexList TestView::selectedRouteRows() const
{
    return _routeView->selectionModel()->selectedRows();
}

QModelIndexList TestView::selectedPointRows() const
{
    return _pointView->selectionModel()->selectedRows();
}

void TestView::setUndoEnabled(bool)
{
}

void TestView::setRedoEnabled(bool)
{
}

bool operator==(const TestView &first, const TestView &second)
{
    if (*(first.routeView()) != *(second.routeView()))
        return false;
    if (*(first.pointView()) != *(second.pointView()))
        return false;
    if (*(first.graphPlot()) != *(second.graphPlot()))
        return false;
    if (first.polylineEdit()->toPlainText() != second.polylineEdit()->toPlainText())
        return false;
    return true;
}

bool operator!=(const TestView &first, const TestView &second)
{
    return !(first == second);
}

void TestView::setPolyline(const QString &polyline)
{
    _polylineEdit->setText(polyline);
}

void TestView::updateRouteView(const QModelIndex &topLeft,
                               const QModelIndex &bottomRight,
                               RouteTableModel *model)
{
    _routeView->updateModel(topLeft, bottomRight, model);
}

void TestView::updatePointView(const QModelIndex &topLeft,
                               const QModelIndex &bottomRight,
                               PointTableModel *model)
{
    _pointView->updateModel(topLeft, bottomRight, model);
}

void TestView::showErrorMessage(const QString &)
{
}

void TestView::selectRoute(int row)
{
    _routeView->selectRow(row);
}

void TestView::setRouteView(RouteTableModel *model)
{
    QModelIndex topLeft = model->index(0, 0);
    QModelIndex bottomRight = model->index(model->rowCount()-1, model->columnCount()-1);
    updateRouteView(topLeft, bottomRight, model);
}

void TestView::setPointView(PointTableModel *model)
{
    QModelIndex topLeft = model->index(0, 0);
    QModelIndex bottomRight = model->index(model->rowCount()-1, model->columnCount()-1);
    updatePointView(topLeft, bottomRight, model);
}

