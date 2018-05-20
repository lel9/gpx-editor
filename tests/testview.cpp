#include "testview.h"

TestView::TestView(const QVector<RouteData> routes, QVector<PointData> points) :
    _routeData(routes), _pointData(points), selectedRouteRow(0), selectedPointRow(0)
{
}

TestView::TestView(const TestView &other) :
    QObject()
{
    _routeData = other._routeData;
    _pointData = other._pointData;
    selectedPointRow = other.selectedPointRow;
    selectedRouteRow = other.selectedRouteRow;
    _polyline = other._polyline;
    _plotKeys = other._plotKeys;
    _plotValues = other._plotValues;
}

TestView::~TestView()
{
}

#include <QStandardItemModel>
QModelIndexList TestView::selectedRouteRows() const
{
    QModelIndexList list;
    QStandardItemModel model;
    model.setRowCount(_routeData.length());
    model.setColumnCount(3);
    list.append(model.index(selectedRouteRow, 0));
    return list;
}

QModelIndexList TestView::selectedPointRows() const
{
    QModelIndexList list;
    QStandardItemModel model;
    model.setRowCount(_pointData.length());
    model.setColumnCount(3);
    list.append(model.index(selectedPointRow, 0));
    return list;
}

QString TestView::polyline() const
{
    return _polyline;
}

QVariant TestView::routeData(const QModelIndex &index) const
{
    switch (index.column())
    {
    case 0:
        return _routeData[index.row()].name;
        break;
    case 1:
        return _routeData[index.row()].distance;
        break;
    case 2:
        return _routeData[index.row()].date;
        break;
    default:
        break;
    }
    return QVariant();
}

QVariant TestView::pointData(const QModelIndex &index) const
{
    switch (index.column())
    {
    case 0:
        return _pointData[index.row()].lat;
        break;
    case 1:
        return _pointData[index.row()].lon;
        break;
    case 2:
        return _pointData[index.row()].alt;
        break;
    default:
        break;
    }
    return QVariant();
}

int TestView::routeViewRow() const
{
    return _routeData.length();
}

int TestView::pointViewRow() const
{
    return _pointData.length();
}

int TestView::routeViewColumn() const
{
    return 3;
}

int TestView::pointViewColumn() const
{
    return 3;
}

QVector<double> TestView::plotKeys() const
{
    return _plotKeys;
}

QVector<double> TestView::plotValues() const
{
    return _plotValues;
}

void TestView::setUndoEnabled(bool)
{
}

void TestView::setRedoEnabled(bool)
{
}

BaseView *TestView::copy()
{
    TestView *view = new TestView(*this);
    return view;
}

bool operator==(const TestView &first, const TestView &second)
{
    if (first._routeData != second._routeData)
        return false;
    if (first._pointData != second._pointData)
        return false;
    if (first._polyline != second._polyline)
        return false;
    if (first._plotKeys != second._plotKeys)
        return false;
    if (first._plotValues != second._plotValues)
        return false;
    return true;
}

bool operator!=(const TestView &first, const TestView &second)
{
    return !(first == second);
}

void TestView::setPolyline(const QString &polyline)
{
    _polyline = polyline;
}

void TestView::setRouteViewSize(int rowCount, int columnCount)
{
    Q_UNUSED(columnCount)
    _routeData.resize(rowCount);
}

void TestView::setPointViewSize(int rowCount, int columnCount)
{
    Q_UNUSED(columnCount)
    _pointData.resize(rowCount);
}

void TestView::setRouteViewHeaders(const QStringList &)
{
}

void TestView::setPointViewHeaders(const QStringList &)
{
}

void TestView::updateRouteView(const QModelIndex &index, const QVariant &data)
{
    switch (index.column())
    {
    case 0:
        _routeData[index.row()].name = data.toString();
        break;
    case 1:
        _routeData[index.row()].distance = data.toDouble();
        break;
    case 2:
        _routeData[index.row()].date = data.toDate();
        break;
    default:
        break;
    }
}

void TestView::updatePointView(const QModelIndex &index, const QVariant &data)
{
    switch (index.column())
    {
    case 0:
        _pointData[index.row()].lat = data.toDouble();
        break;
    case 1:
        _pointData[index.row()].lon = data.toDouble();
        break;
    case 2:
        _pointData[index.row()].alt = data.toDouble();
        break;
    default:
        break;
    }
}

void TestView::setPlotData(const QVector<double> &keys, const QVector<double> &values)
{
    _plotKeys = keys;
    _plotValues = values;
}

void TestView::showErrorMessage(const QString &)
{
}

void TestView::selectRoute(int row)
{
    selectedRouteRow = row;
}

