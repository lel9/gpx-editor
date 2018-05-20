#ifndef ROUTE_H
#define ROUTE_H

#include <QVector>
#include <QDate>
#include <QGeoCoordinate>

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

    QList<QGeoCoordinate> _points;

private:
    void updatePolyline();

public:
    Route();
    Route(const Route &other);
    ~Route();

    QDate date() const;
    QString name() const;
    QString polyline();
    double distance();
    const QList<QGeoCoordinate> &points() const;

    QGeoCoordinate pointAt(int pos) const;
    int length() const;

    void setDate(const QDate &date);
    void setName(const QString &name);
    void setDistance(double dist);
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
