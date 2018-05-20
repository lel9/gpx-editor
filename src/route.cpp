#include "route.h"
#include "converter.h"

Route::Route() :
    _date(QDate::currentDate()),
    _name("Новый маршрут"),
    _dist(0),
    _dirtyDist(false),
    _dirtyPolyline(false)
{
}

Route::Route(const Route &other) :
    _date(other._date),
    _name(other._name),
    _dist(other._dist),
    _dirtyDist(other._dirtyDist),
    _dirtyPolyline(other._dirtyPolyline),
    _points(other._points)
{
}

Route::~Route()
{
}

QDate Route::date() const
{
    return _date;
}

QString Route::name() const
{
    return _name;
}

QString Route::polyline()
{
    if (_dirtyPolyline)
    {
        updatePolyline();
        _dirtyPolyline = false;
    }
    return _polyline;
}

QGeoCoordinate Route::pointAt(int pos) const
{
    return _points[pos];
}

int Route::length() const
{
    return _points.length();
}

double Route::distance()
{
    if (_dirtyDist)
    {
        _dist = 0;
        int n = _points.length() - 1;
        for (int i = 0; i < n; i++)
            _dist += _points[i].distanceTo(_points[i+1]) / 1000.;
        _dirtyDist = false;
    }
    return _dist;
}

const QList<QGeoCoordinate> &Route::points() const
{
    return _points;
}

void Route::setDate(const QDate &date)
{
    _date = date;
}

void Route::setName(const QString &name)
{
    _name = name;
}

void Route::setDistance(double dist)
{
    _dist = dist;
}

void Route::setPolyline(const QString &polyline)
{
    _polyline = polyline;
}

void Route::updatePolyline()
{
    shared_ptr<Route> route = make_shared<Route>(*this);
    _polyline = Converter::routeToPolyline(route);
}

void Route::insertPoint(int pos, const QGeoCoordinate &point)
{
    _dirtyPolyline = _dirtyDist = true;
    _points.insert(pos, point);
}

void Route::appendPoint(const QGeoCoordinate &point)
{
    _dirtyPolyline = _dirtyDist = true;
    _points.append(point);
}

QGeoCoordinate Route::removePoint(int pos)
{
    _dirtyPolyline = _dirtyDist = true;
    QGeoCoordinate ret = _points.at(pos);
    _points.removeAt(pos);
    return ret;
}

QGeoCoordinate Route::replacePoint(int pos, const QGeoCoordinate &point)
{
    _dirtyPolyline = _dirtyDist = true;
    QGeoCoordinate ret = _points.at(pos);
    _points[pos] = point;
    return ret;
}

bool operator !=(const Route &first, const Route &second)
{
    if (first.length() != second.length())
        return true;
    int n = first.length();
    for (int i = 0; i < n; i++)
        if (first.pointAt(i) != second.pointAt(i))
            return true;
    return false;
}

bool operator ==(const Route &first, const Route &second)
{
    if (first.length() != second.length())
        return false;
    int n = first.length();
    for (int i = 0; i < n; i++)
        if (first.pointAt(i) != second.pointAt(i))
            return false;
    return true;
}

