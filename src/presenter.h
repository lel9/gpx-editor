#ifndef PRESENTER_H
#define PRESENTER_H

#include "route_table_model.h"
#include "baseview.h"
#include "command.h"

#include <QStack>

class Presenter : public QObject
{
    Q_OBJECT

private:
    RouteTableModel *model;
    BaseView *view;

    QStack<Command*> commandUndoStack;
    QStack<Command*> commandRedoStack;

public:
    Presenter(BaseView *view);
    ~Presenter();

public slots:
    void on_importFromGPX(QString filename);
    void on_importFromPolyline(QString filename);

    void on_addRoute();
    void on_deleteRoute();

    void on_currentRouteChanged();
    void on_routesChanged(QModelIndex topLeft, QModelIndex bottomRight);

    void on_insertPoint(InsertPointPos pos);
    void on_deletePoint();
    void on_pointChanged(QModelIndex index, double val);
    void on_pointDataChanged(QModelIndex topLeft, QModelIndex bottomRight);

    void on_redo();
    void on_undo();

private:
    void executeCommand(Command *command);
};

#endif // PRESENTER_H
