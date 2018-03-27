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
    RouteLoader() = default;
    virtual ~RouteLoader();
    virtual void setFileName(const QString &filename);
    virtual QVector<shared_ptr<Route>> load() = 0;
};


class GPXLoader : public RouteLoader
{
public:
    GPXLoader() = default;
    ~GPXLoader() = default;
    virtual QVector<shared_ptr<Route>> load() override;
};

class PolylineLoader : public RouteLoader
{
public:
    PolylineLoader() = default;
    ~PolylineLoader() = default;
    virtual QVector<shared_ptr<Route>> load() override;
};

#endif // ROUTELOADER_H
