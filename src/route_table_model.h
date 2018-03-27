#ifndef ROUTETABLEMODEL_H
#define ROUTETABLEMODEL_H

#include <QAbstractTableModel>
#include "route.h"
#include "route_saver.h"

class  RouteTableModel : public QAbstractTableModel
{
public:
    RouteTableModel(QObject *parent = 0);
    RouteTableModel(const RouteTableModel &model);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void addRoute(const shared_ptr<Route> &route);
    void insertRoute(int row, const shared_ptr<Route> &route);
    shared_ptr<Route> removeRoute(int row);

    void saveRoutes(const shared_ptr<RouteSaver> &saver);

    shared_ptr<Route> currentRoute();
    void setCurrentRoute(int row);

    // для тестов
    RouteTableModel& operator =(const RouteTableModel &model);
    friend bool operator ==(const RouteTableModel &first, const RouteTableModel &second);

private:
    QVector<shared_ptr<Route>> _routes;
    int currentRouteIndex;


};

#endif // ROUTETABLEMODEL_H
