#ifndef ROUTETABLEMODEL_H
#define ROUTETABLEMODEL_H

#include <QAbstractTableModel>
#include "route_saver.h"
#include "route_loader.h"

class  RouteTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    QVector<shared_ptr<Route>> _routes;
    int currentIndex;

    QString dataPath; // куда сохранять данные после завершения программы

public:
    RouteTableModel(QObject *parent = 0);
    RouteTableModel(const RouteTableModel &model);
    ~RouteTableModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;


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
    double replacePointInCurrentRoute(QModelIndex index, double val);

    QString currentPolyline();
    PointTableModel *currentPointModel() const;

    int currentRoute();
    void setCurrentRoute(int row);

signals:
    void pointDataChanged(QModelIndex, QModelIndex);
    void currentRouteChanged(int);

public:
    // для тестов
    RouteTableModel& operator =(const RouteTableModel &model);
    friend bool operator ==(const RouteTableModel &first, const RouteTableModel &second);

private:
    void loadRoutes(shared_ptr<RouteLoader> loader);
};

#endif // ROUTETABLEMODEL_H
