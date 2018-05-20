#include "route_table_model.h"

#include <QStandardPaths>
#include <QDir>

RouteTableModel::RouteTableModel() :
   currentIndex(0)
{
}

RouteTableModel::RouteTableModel(const RouteTableModel &model) :
    currentIndex(model.currentIndex)
{
    for (auto el : model._routes)
       _routes << el;
}

RouteTableModel::~RouteTableModel()
{
}

int RouteTableModel::routesCount() const
{
    return _routes.count();
}

const QVector<shared_ptr<Route>> &RouteTableModel::routes() const
{
    return _routes;
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
    emit dataChanged(_routes.length()-1, _routes.length()-1);

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
    emit dataChanged(row, _routes.length()-1);

    currentIndex = row;
    emit currentRouteChanged(currentIndex);
}

shared_ptr<Route> RouteTableModel::removeRoute(int row)
{
    if (row < 0 || row >= _routes.length())
        throw out_of_range("Невозможно удалить маршрут: некорректный индекс");

    shared_ptr<Route> route = _routes.at(row);
    _routes.remove(row);
    emit dataChanged(row, _routes.length()-1);

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
    emit pointDataChanged(pos, currentRoute->length()-1);
}

QGeoCoordinate RouteTableModel::removePointFromCurrentRoute(int pos)
{
    shared_ptr<Route> currentRoute = _routes[currentIndex];
    QGeoCoordinate point = currentRoute->removePoint(pos);
    emit pointDataChanged(pos, currentRoute->length()-1);
    return point;
}

QGeoCoordinate RouteTableModel::replacePointInCurrentRoute(int pos, const QGeoCoordinate &point)
{
    QGeoCoordinate oldPoint = _routes[currentIndex]->replacePoint(pos, point);
    emit pointDataChanged(pos, pos);
    return oldPoint;
}

void RouteTableModel::setCurrentRouteName(const QString &name)
{
    _routes[currentIndex]->setName(name);
}

QString RouteTableModel::currentPolyline()
{
    return _routes[currentIndex]->polyline();
}

double RouteTableModel::currentDistance()
{
    return _routes[currentIndex]->distance();
}

const QList<QGeoCoordinate> &RouteTableModel::currentPoints()
{
    return _routes[currentIndex]->points();
}

bool RouteTableModel::altitudeMap(QVector<double> &dist, QVector<double> &alt)
{
    dist.clear();
    alt.clear();

    double currDist = 0;
    int len = _routes[currentIndex]->length();
    for (int i = 0; i < len-1; i++)
    {
        dist << currDist;
        QGeoCoordinate point = _routes[currentIndex]->pointAt(i);
        QGeoCoordinate nextPoint = _routes[currentIndex]->pointAt(i+1);
        currDist += point.distanceTo(nextPoint) / 1000.;
        alt << point.altitude();
    }
    if (len > 0)
    {
        dist << currDist;
        alt << _routes[currentIndex]->pointAt(len-1).altitude();
    }
    return true;
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

int RouteTableModel::currentRouteIndex()
{
    return currentIndex;
}

void RouteTableModel::setCurrentRouteIndex(int row)
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
    emit dataChanged(oldLen, _routes.length()-1);

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

bool operator !=(const RouteTableModel &first, const RouteTableModel &second)
{
    return !(first == second);
}
