#include "presenter.h"

#include "add_route_command.h"
#include "remove_route_command.h"
#include "add_point_command.h"
#include "remove_point_command.h"
#include "edit_point_command.h"

#include "model_index_iterator.h"

Presenter::Presenter(BaseView *view) :
    view(view)
{
    model = new RouteTableModel;
    setHeaders();
    initConnections();
    visitorManager.manage();
}

Presenter::Presenter(BaseView *view, RouteTableModel *model) :
    model(model), view(view)
{
    setHeaders();
    initConnections();
    visitorManager.manage();
}

Presenter::Presenter(const Presenter &other) :
    QObject()
{
    model = new RouteTableModel;
    *model = *(other.model);
    view = other.view->copy();
    setHeaders();
    initConnections();
    visitorManager.manage();
}

Presenter::~Presenter()
{
    delete model;
}

void Presenter::recoverRoutes()
{
    model->recoverRoutes();
}

void Presenter::saveRoutes()
{
    model->saveRoutes();
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
    commandManager.addCommand(new AddRouteCommand(model));
}

void Presenter::on_deleteRoute()
{
    int row = view->selectedRouteRow();
    commandManager.addCommand(new RemoveRouteCommand(row, model));
}

void Presenter::on_routeNameChanged(const QString &name)
{
    model->setCurrentRouteName(name);
}

void Presenter::on_currentRouteChanged()
{
    int index = view->selectedRouteRow();
    if (index >= 0)
    {
        model->setCurrentRouteIndex(index);

        const QList<QGeoCoordinate> &points = model->currentPoints();
        updatePointView(points);
        updatePlotData();

        try
        {
            view->setPolyline(model->currentPolyline());
        }
        catch(std::exception &ex)
        {
            view->showErrorMessage(ex.what());
        }
    }
}

void Presenter::addOperation(Visitor *visitor)
{
    view->addOperation(visitor->operationName());
}

void Presenter::on_insertPoint(InsertPointPos pos)
{
    int selectedRoute = view->selectedRouteRow();
    int selectedPoint = view->selectedPointRow();
    if (selectedRoute >= 0)
    {
        if (selectedPoint >= 0)
        {
            int row = view->selectedPointRow() + pos;
            commandManager.addCommand(new AddPointCommand(row, model));
        }
        else if (model->currentPoints().isEmpty())
            commandManager.addCommand(new AddPointCommand(0, model));
    }
}

void Presenter::on_deletePoint()
{
    int selectedRoute = view->selectedRouteRow();
    int selectedPoint = view->selectedPointRow();
    if (selectedRoute >= 0 && selectedPoint >= 0)
        commandManager.addCommand(new RemovePointCommand(selectedPoint, model));
}

void Presenter::on_pointChanged(const TableIndex &index, double val)
{
    commandManager.addCommand(new EditPointCommand(index, val, model));
}

void Presenter::on_pointDataChanged(int topLeft, int bottomRight)
{
    updatePointView(model->currentPoints(), topLeft, bottomRight);
    double dist = updatePlotData();

    try
    {
        view->setPolyline(model->currentPolyline());
    }
    catch(std::exception &ex)
    {
        view->showErrorMessage(ex.what());
    }

    TableIndex routeIndex(model->currentRouteIndex(), 1);
    view->updateRouteView(routeIndex, dist); // длина
}

void Presenter::on_redo()
{
    commandManager.redoCommand();
}

void Presenter::on_undo()
{
    commandManager.undoCommand();
}

void Presenter::executeOperaton(int operationIndex)
{
    view->setOperationResult(visitorManager.accept(model->currentPoints(), operationIndex));
}

void Presenter::on_routesChanged(int topLeft, int bottomRight)
{
    updateRouteView(topLeft, bottomRight);
}

void Presenter::updatePointView(const QList<QGeoCoordinate> &points)
{
    updatePointView(points, 0, points.length()-1);
}

void Presenter::updatePointView(const QList<QGeoCoordinate> &points, int topLeft, int bottomRight)
{
    int rowsCount = points.length();
    view->setPointViewSize(rowsCount, 3);
    if (topLeft >= 0 && bottomRight < rowsCount)
    {
        for (int row = topLeft; row <= bottomRight; row++)
        {
            view->updatePointView(TableIndex(row, 0), points[row].latitude());
            view->updatePointView(TableIndex(row, 1), points[row].longitude());
            view->updatePointView(TableIndex(row, 2), points[row].altitude());
        }
    }
    view->setPointViewHeaders(pointHeaders);
}

void Presenter::updateRouteView(int topLeft, int bottomRight)
{
    const QVector<shared_ptr<Route>> &routes = model->routes();
    view->setRouteViewSize(routes.length(), 3);
    if (topLeft >= 0 && bottomRight < routes.length())
    {
        for (int row = topLeft; row <= bottomRight; row++)
        {
            view->updateRouteView(TableIndex(row, 0), routes[row]->name());
            view->updateRouteView(TableIndex(row, 1), routes[row]->distance());
            view->updateRouteView(TableIndex(row, 2), routes[row]->date());
        }
    }
    view->setRouteViewHeaders(routeHeaders);
}

double Presenter::updatePlotData()
{
    QVector<double> keys, values;
    model->altitudeMap(keys, values);
    view->setPlotData(keys, values);
    if (!keys.isEmpty())
        return keys.last();
    return 0;
}

void Presenter::initConnections()
{
    QObject *objView = dynamic_cast<QObject*>(view);

    connect(objView, SIGNAL(currentRouteChanged()), this, SLOT(on_currentRouteChanged()));

    connect(model, SIGNAL(dataChanged(int,int)), this, SLOT(on_routesChanged(int,int)));
    connect(model, SIGNAL(pointDataChanged(int, int)), this, SLOT(on_pointDataChanged(int, int)));
    connect(model, SIGNAL(currentRouteChanged(int)), objView, SLOT(selectRoute(int)));

    connect(&commandManager, SIGNAL(redoStackIsNotEmpty(bool)), objView, SLOT(setRedoEnabled(bool)));
    connect(&commandManager, SIGNAL(undoStackIsNotEmpty(bool)), objView, SLOT(setUndoEnabled(bool)));

    connect(&visitorManager, SIGNAL(addVisitor(Visitor*)), this, SLOT(addOperation(Visitor*)));
}

void Presenter::setHeaders()
{
    routeHeaders << "Имя" << "Длина, м" << "Дата создания";
    pointHeaders << "Широта" << "Долгота" << "Высота";
}

