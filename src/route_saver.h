#ifndef ROUTESAVER_H
#define ROUTESAVER_H

#include "route.h"

#include <QFile>

class RouteSaver
{
protected:
    QFile file;
public:
    RouteSaver() = default;
    virtual ~RouteSaver();
    virtual void setFileName(const QString &filename);
    virtual void save(const QVector<shared_ptr<Route>> &routes) = 0;
};

class SimpleRouteSaver : public RouteSaver
{
public:
    SimpleRouteSaver() = default;
    virtual ~SimpleRouteSaver() = default;
    virtual void save(const QVector<shared_ptr<Route>> &routes);
};



#endif // ROUTESAVER_H
