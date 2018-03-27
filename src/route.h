#ifndef ROUTE_H
#define ROUTE_H

#include "point_table_model.h"

#include <QVector>
#include <QDate>

#include <memory>
using namespace std;

class Route
{
private:
    QDate _date;
    QString _name;
    QString _polyline;
    double _dist;

    bool _dirtyDist;
    bool _dirtyPolyline;   // чтобы пересчитывать полилайн только когда он изменился

    shared_ptr<PointTableModel> _model;

private:
    void updatePolyline();

public:
    Route();
    ~Route();

    QDate date() const;
    QString name() const;
    QString polyline();
    double distance();
    QGeoCoordinate pointAt(int pos) const;
    int length() const;

    shared_ptr<PointTableModel> model() const;

    void setDate(const QDate &date);
    void setName(const QString &name);
    void setPolyline(const QString &polyline);

    void insertPoint(int pos, const QGeoCoordinate &point);
    void appendPoint(const QGeoCoordinate &point);
    QGeoCoordinate removePoint(int pos);
    QGeoCoordinate replacePoint(int pos, const QGeoCoordinate &point);

    // для тестов
    friend bool operator ==(const Route &first, const Route &second);
    friend bool operator !=(const Route &first, const Route &second);
};

#endif // ROUTE_H
