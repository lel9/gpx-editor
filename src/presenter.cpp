#include "presenter.h"

#include "add_route_command.h"
#include "remove_route_command.h"
#include "add_point_command.h"
#include "remove_point_command.h"
#include "edit_point_command.h"

Presenter::Presenter(BaseView *view) :
    view(view)
{
    model = new RouteTableModel;

    connect(view, SIGNAL(importFromGPX(QString)),
            this, SLOT(on_importFromGPX(QString)));
    connect(view, SIGNAL(importFromPolyline(QString)),
            this, SLOT(on_importFromPolyline(QString)));
    connect(view, SIGNAL(addRoute()),
            this, SLOT(on_addRoute()));
    connect(view, SIGNAL(deleteRoute()),
            this, SLOT(on_deleteRoute()));
    connect(view, SIGNAL(insertPoint(InsertPointPos)),
            this, SLOT(on_insertPoint(InsertPointPos)));
    connect(view, SIGNAL(deletePoint()),
            this, SLOT(on_deletePoint()));
    connect(view, SIGNAL(pointChanged(QModelIndex,double)),
            this, SLOT(on_pointChanged(QModelIndex,double)));
    connect(view, SIGNAL(currentRouteChanged()),
            this, SLOT(on_currentRouteChanged()));

    connect(view, SIGNAL(redo()),
            this, SLOT(on_redo()));
    connect(view, SIGNAL(undo()),
            this, SLOT(on_undo()));

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(on_routesChanged(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(pointDataChanged(QModelIndex,QModelIndex)),
            this, SLOT(on_pointDataChanged(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(currentRouteChanged(int)),
            view, SLOT(selectRoute(int)));

    model->recoverRoutes();
}

Presenter::~Presenter()
{
    model->saveRoutes();
    delete model;
}

void Presenter::on_importFromGPX(QString filename)
{
    if (!filename.isEmpty())
    {
        try
        {
            model->loadRoutesFromGPX(filename);
        }
        catch (std::exception &ex)
        {
            view->showErrorMessage(QString::fromUtf8(ex.what()));
        }
    }
}

void Presenter::on_importFromPolyline(QString filename)
{
    if (!filename.isEmpty())
    {
        try
        {
            model->loadRoutesFromPolyline(filename);
        }
        catch (std::exception &ex)
        {
            view->showErrorMessage(QString::fromUtf8(ex.what()));
        }
    }
}

void Presenter::on_addRoute()
{
    executeCommand(new AddRouteCommand(model));
}

void Presenter::on_deleteRoute()
{
    QModelIndexList rows = view->selectedRouteRows();
    if (!rows.isEmpty())
        executeCommand(new RemoveRouteCommand(rows[0].row(), model));
}

void Presenter::on_currentRouteChanged()
{
    if (!view->selectedRouteRows().isEmpty())
    {
        int index = view->selectedRouteRows()[0].row();
        model->setCurrentRoute(index);
        PointTableModel *pModel = model->currentPointModel();
        view->updatePointView(pModel->topLeftIndex(), pModel->bottomRightIndex(), pModel);
        try
        {
            view->setPolyline(model->currentPolyline());
        }
        catch(std::exception &) { }
    }
}

void Presenter::on_insertPoint(InsertPointPos pos)
{
    if (!view->selectedRouteRows().isEmpty())
    {
        if (!view->selectedPointRows().isEmpty())
        {
            int row = view->selectedPointRows()[0].row() + pos;
            executeCommand(new AddPointCommand(row, model));
        }
        else if (model->currentPointModel()->rowCount() == 0)
            executeCommand(new AddPointCommand(0, model));
    }
}

void Presenter::on_deletePoint()
{
    if (!view->selectedRouteRows().isEmpty() && !view->selectedPointRows().isEmpty())
    {
        int row = view->selectedPointRows()[0].row();
        executeCommand(new RemovePointCommand(row, model));
    }
}

void Presenter::on_pointChanged(QModelIndex index, double val)
{
    executeCommand(new EditPointCommand(index, val, model));
}

void Presenter::on_pointDataChanged(QModelIndex topLeft, QModelIndex bottomRight)
{
    view->updatePointView(topLeft, bottomRight, model->currentPointModel());

    try
    {
        view->setPolyline(model->currentPolyline());
    }
    catch(std::exception &ex)
    {
        view->showErrorMessage(ex.what());
    }
    QModelIndex routeIndex = model->index(model->currentRoute(), 1);
    view->updateRouteView(routeIndex, routeIndex, model); // длина
}

void Presenter::on_redo()
{
    Command *command = commandRedoStack.pop();
    if (command->execute() == 0)
    {
        commandUndoStack.push(command);
        view->setUndoEnabled(true);
        if (commandRedoStack.isEmpty())
            view->setRedoEnabled(false);
    }
}

void Presenter::on_undo()
{
    Command *command = commandUndoStack.pop();
    if (command->unExecute() == 0)
    {
        commandRedoStack.push(command);
        view->setRedoEnabled(true);
        if (commandUndoStack.isEmpty())
            view->setUndoEnabled(false);
    }
}

void Presenter::on_routesChanged(QModelIndex topLeft, QModelIndex bottomRight)
{
    view->updateRouteView(topLeft, bottomRight, model);
}

void Presenter::executeCommand(Command *command)
{
    if (command->execute() == 0)
    {
        commandUndoStack.push(command);
        view->setUndoEnabled(true);
    }
}

