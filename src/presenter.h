#ifndef PRESENTER_H
#define PRESENTER_H

#include "route_table_model.h"
#include "baseview.h"
#include "command_manager.h"
#include "visitor_manager.h"

#include <QStack>

class Presenter : public QObject
{
    Q_OBJECT

private:
    RouteTableModel *model;
    BaseView *view;
    CommandManager commandManager;
    VisitorManager visitorManager;

    QStringList routeHeaders;
    QStringList pointHeaders;

public:
    Presenter() { }
    Presenter(BaseView *view);
    Presenter(BaseView *view, RouteTableModel *model);
    Presenter(const Presenter &other);
    ~Presenter();

    void recoverRoutes();
    void saveRoutes();
    void on_importFromGPX(QString filename);
    void on_importFromPolyline(QString filename);

    void on_addRoute();
    void on_deleteRoute();
    void on_routeNameChanged(const QString &name);

    void on_insertPoint(InsertPointPos pos);
    void on_deletePoint();
    void on_pointChanged(const TableIndex &index, double val);

    void on_redo();
    void on_undo();

    void executeOperaton(int operationIndex);

private slots:
    void on_pointDataChanged(int topLeft, int bottomRight);
    void on_routesChanged(int topLeft, int bottomRight);
    void on_currentRouteChanged();

    void addOperation(Visitor *visitor);

private:
    void updatePointView(const QList<QGeoCoordinate> &points);
    void updatePointView(const QList<QGeoCoordinate> &points,
                         int topLeft, int bottomRight);
    void updateRouteView(int topLeft, int bottomRight);
    double updatePlotData();
    void initConnections();
    void setHeaders();
};

#endif // PRESENTER_H
