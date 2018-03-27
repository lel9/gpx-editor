#include "route.h"
#include "converter.h"

Route::Route() :
    _date(QDate::currentDate()),
    _name("Новый маршрут"),
    _dist(0),
    _dirtyDist(false),
    _dirtyPolyline(false)
{
    _model = make_shared<PointTableModel>();
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
    return _model->pointAt(pos);
}

int Route::length() const
{
    return _model->rowCount();
}

double Route::distance()
{
    if (_dirtyDist)
    {
        _dist = _model->distance();
        _dirtyDist = false;
    }
    return _dist;
}

shared_ptr<PointTableModel> Route::model() const
{
    return _model;
}

void Route::setDate(const QDate &date)
{
    _date = date;
}

void Route::setName(const QString &name)
{
    _name = name;
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
    _model->insertPoint(pos, point);
}

void Route::appendPoint(const QGeoCoordinate &point)
{
    _dirtyPolyline = _dirtyDist = true;
    _model->addPoint(point);
}

QGeoCoordinate Route::removePoint(int pos)
{
    _dirtyPolyline = _dirtyDist = true;
    return _model->removePoint(pos);
}

QGeoCoordinate Route::replacePoint(int pos, const QGeoCoordinate &point)
{
    _dirtyPolyline = _dirtyDist = true;
    return _model->replacePoint(pos, point);
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

