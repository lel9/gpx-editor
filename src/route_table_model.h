#ifndef ROUTETABLEMODEL_H
#define ROUTETABLEMODEL_H

#include <QObject>
#include "route_saver.h"
#include "route_loader.h"

class  RouteTableModel : public QObject
{
    Q_OBJECT

private:
    QVector<shared_ptr<Route>> _routes;
    int currentIndex;

    QString dataPath; // куда сохранять данные после завершения программы

public:
    RouteTableModel();
    RouteTableModel(const RouteTableModel &model);
    ~RouteTableModel();

    int routesCount() const;
    const QVector<shared_ptr<Route>> &routes() const;

    void recoverRoutes();
    void saveRoutes();

    void loadRoutesFromPolyline(const QString &filename);
    void loadRoutesFromGPX(const QString &filename);

    void addRoute(const shared_ptr<Route> &route);
    void addRoute();
    void insertRoute(int row, const shared_ptr<Route> &route);
    shared_ptr<Route> removeRoute(int row);

    void insertPointToCurrentRoute(int pos);
    void insertPointToCurrentRoute(int pos, const QGeoCoordinate &point);
    QGeoCoordinate removePointFromCurrentRoute(int pos);
    QGeoCoordinate replacePointInCurrentRoute(int pos, const QGeoCoordinate &point);

    void setCurrentRouteName(const QString &name);
    QString currentPolyline();
    double currentDistance();
    const QList<QGeoCoordinate> &currentPoints();

    bool altitudeMap(QVector<double> &dist, QVector<double> &alt);

    int currentRouteIndex();
    void setCurrentRouteIndex(int row);

signals:
    void pointDataChanged(int, int);
    void dataChanged(int, int);
    void currentRouteChanged(int);

public:
    // для тестов
    RouteTableModel& operator =(const RouteTableModel &model);
    friend bool operator ==(const RouteTableModel &first, const RouteTableModel &second);
    friend bool operator !=(const RouteTableModel &first, const RouteTableModel &second);

private:
    void loadRoutes(shared_ptr<RouteLoader> loader);
};

#endif // ROUTETABLEMODEL_H
