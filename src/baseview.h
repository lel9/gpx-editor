#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QString>
#include <QTableWidget>
#include <QMainWindow>
#include "enum_insert_point.h"
#include "route_table_model.h"

class BaseView : public QMainWindow
{
    Q_OBJECT

public:
    BaseView(QWidget *parent = 0);

    virtual QTableWidget* routeView() const = 0;
    virtual QTableWidget* pointView() const = 0;

    virtual QModelIndexList selectedRouteRows() const = 0;
    virtual QModelIndexList selectedPointRows() const = 0;

    virtual void setUndoEnabled(bool enable) = 0;
    virtual void setRedoEnabled(bool enable) = 0;

public slots:
    virtual void setPolyline(const QString &polyline) = 0;
    virtual void updateRouteView(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  RouteTableModel *model) = 0;
    virtual void updatePointView(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  PointTableModel *model) = 0;

    virtual void showErrorMessage(const QString &message) = 0;

    virtual void selectRoute(int row) = 0;

signals:
    void importFromGPX(QString);
    void importFromPolyline(QString);
    void addRoute();
    void deleteRoute();

    void currentRouteChanged();

    void undo();
    void redo();

    void insertPoint(InsertPointPos);
    void deletePoint();
    void pointChanged(QModelIndex, double);
};

#endif // BASEVIEW_H
