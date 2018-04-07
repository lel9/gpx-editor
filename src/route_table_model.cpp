#include "route_table_model.h"
#include "point_table_model.h"

#include <QStandardPaths>
#include <QDir>

RouteTableModel::RouteTableModel(QObject *parent) :
    QAbstractTableModel(parent), currentIndex(0)
{
}

RouteTableModel::RouteTableModel(const RouteTableModel &model) :
    QAbstractTableModel(),
    _routes(model._routes), currentIndex(model.currentIndex)
{
}

RouteTableModel::~RouteTableModel()
{
}

int RouteTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _routes.count();
}

int RouteTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant RouteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Vertical)
        return section;

    switch(section)
    {
    case 0:
        return trUtf8("Имя");
    case 1:
        return trUtf8("Длина, м");
    case 2:
        return trUtf8("Дата создания");
    }

    return QVariant();
}

QVariant RouteTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || _routes.count() <= index.row() ||
        (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    switch(index.column())
    {
    case 0:
        return _routes[index.row()]->name();
    case 1:
        return _routes[index.row()]->distance();
    case 2:
        return _routes[index.row()]->date();
    }
    return QVariant();
}

bool RouteTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || role != Qt::EditRole || _routes.count() <= index.row())
        return false;

    switch(index.column())
    {
    case 0:
        _routes[index.row()]->setName(value.toString());
        break;
    default:
        return false;
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags RouteTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (index.column() == 0)
        flags |= Qt::ItemIsEditable;
    return flags;
}

PointTableModel *RouteTableModel::currentPointModel() const
{
    return _routes[currentIndex]->model().get();
}

void RouteTableModel::recoverRoutes()
{
    dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(dataPath);
    if (!dir.exists())
        dir.mkpath(dataPath);
    dataPath = dir.absoluteFilePath("routes.xml");

    try
    {
        loadRoutesFromPolyline(dataPath);
    }
    catch(std::exception &) { }
}

#include "route_loader.h"
void RouteTableModel::loadRoutesFromPolyline(const QString &filename)
{
    shared_ptr<RouteLoader> loader = make_shared<PolylineLoader>();
    loader->setFileName(filename);
    loadRoutes(loader);
}

void RouteTableModel::loadRoutesFromGPX(const QString &filename)
{
    shared_ptr<RouteLoader> loader = make_shared<GPXLoader>();
    loader->setFileName(filename);
    loadRoutes(loader);
}

void RouteTableModel::addRoute(const shared_ptr<Route> &route)
{
    _routes.append(route);
    emit dataChanged(createIndex(_routes.length()-1, 0), createIndex(rowCount()-1, columnCount()-1));

    currentIndex = _routes.length()-1;
    emit currentRouteChanged(currentIndex);
}

void RouteTableModel::addRoute()
{
    addRoute(make_shared<Route>());
}

void RouteTableModel::insertRoute(int row, const shared_ptr<Route> &route)
{
    _routes.insert(row, route);
    emit dataChanged(createIndex(row, 0), createIndex(rowCount()-1, columnCount()-1));

    currentIndex = row;
    emit currentRouteChanged(currentIndex);
}

shared_ptr<Route> RouteTableModel::removeRoute(int row)
{
    if (row < 0 || row >= _routes.length())
        throw out_of_range("Невозможно удалить маршрут: некорректный индекс");

    shared_ptr<Route> route = _routes.at(row);
    _routes.remove(row);
    emit dataChanged(createIndex(row, 0), createIndex(rowCount()-1, columnCount()-1));

    if (_routes.length() > 0)
    {
        if (row == _routes.length())
            currentIndex = row-1;
        else
            currentIndex = row;
        emit currentRouteChanged(currentIndex);
    }

    return route;
}

void RouteTableModel::insertPointToCurrentRoute(int pos)
{
   insertPointToCurrentRoute(pos, QGeoCoordinate(0,0));
}

void RouteTableModel::insertPointToCurrentRoute(int pos, const QGeoCoordinate &point)
{
    shared_ptr<Route> currentRoute = _routes[currentIndex];
    currentRoute->insertPoint(pos, point);

    PointTableModel *pointModel = currentRoute->model().get();
    emit pointDataChanged(pointModel->index(pos, 0), pointModel->bottomRightIndex());
}

QGeoCoordinate RouteTableModel::removePointFromCurrentRoute(int pos)
{
    shared_ptr<Route> currentRoute = _routes[currentIndex];
    QGeoCoordinate point = currentRoute->removePoint(pos);

    PointTableModel *pointModel = currentRoute->model().get();
    emit pointDataChanged(pointModel->index(pos, 0), pointModel->bottomRightIndex());

    return point;
}

double RouteTableModel::replacePointInCurrentRoute(QModelIndex index, double val)
{
    double oldPoint = _routes[currentIndex]->replacePoint(index, val);
    emit pointDataChanged(index, index);
    return oldPoint;
}

QString RouteTableModel::currentPolyline()
{
    return _routes[currentIndex]->polyline();
}

void RouteTableModel::saveRoutes()
{
    SimpleRouteSaver saver;
    saver.setFileName(dataPath);
    try
    {
        saver.save(_routes);
    }
    catch (std::exception &) { }
}

int RouteTableModel::currentRoute()
{
    return currentIndex;
}

void RouteTableModel::setCurrentRoute(int row)
{
    if (row >=0 && row < _routes.length())
        currentIndex = row;
    else
        currentIndex = 0;
}

void RouteTableModel::loadRoutes(shared_ptr<RouteLoader> loader)
{
    int oldLen = _routes.length();
    _routes.append(loader->load());
    emit dataChanged(createIndex(oldLen, 0), createIndex(rowCount()-1, columnCount()-1));

    currentIndex = _routes.length()-1;
    emit currentRouteChanged(currentIndex);
}

RouteTableModel& RouteTableModel::operator =(const RouteTableModel &model)
{
    _routes = model._routes;
    currentIndex = model.currentIndex;
    return *this;
}

bool operator ==(const RouteTableModel &first, const RouteTableModel &second)
{
    if (first._routes.length() != second._routes.length())
        return false;
    int n = first._routes.length();
    for (int i = 0; i < n; i++)
        if (*(first._routes[i]) != *(second._routes[i]))
            return false;
    return true;
}
