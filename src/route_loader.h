#ifndef ROUTELOADER_H
#define ROUTELOADER_H

#include "route.h"

#include <QFile>
#include <QXmlStreamReader>

class RouteLoader
{
protected:
    QFile file;
public:
    RouteLoader() { }
    virtual ~RouteLoader();
    virtual void setFileName(const QString &filename);
    virtual QVector<shared_ptr<Route>> load() = 0;
};


class GPXLoader : public RouteLoader
{
public:
    GPXLoader() { }
    ~GPXLoader() = default;
    virtual QVector<shared_ptr<Route>> load() override;
protected:
    virtual bool loadAltitude(QXmlStreamReader &inputStream, QGeoCoordinate &point);
    virtual QGeoCoordinate loadPoint(QXmlStreamReader &inputStream, bool *ok = 0);
};

class PolylineLoader : public RouteLoader
{
public:
    PolylineLoader() { }
    ~PolylineLoader() = default;
    virtual QVector<shared_ptr<Route>> load() override;
protected:
    virtual bool loadAltitudes(QXmlStreamReader &inputStream, shared_ptr<Route> &route);
};

#endif // ROUTELOADER_H
