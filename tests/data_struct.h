#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <QString>
#include <QDate>

struct RouteData
{
    QString name;
    double distance;
    QDate date;

    friend bool operator ==(const RouteData &first, const RouteData &second);
    friend bool operator !=(const RouteData &first, const RouteData &second);
};

struct PointData
{
    double lat;
    double lon;
    double alt;

    friend bool operator ==(const PointData &first, const PointData &second);
    friend bool operator !=(const PointData &first, const PointData &second);
};

#endif // DATA_STRUCT_H
