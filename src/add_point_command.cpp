#include "add_point_command.h"
#include "remove_point_command.h"

AddPointCommand::AddPointCommand(int pos, RouteTableModel *model) :
    _pos(pos), _point(0, 0, 0), _model(model)
{
    _route = _model->currentRouteIndex();
}

AddPointCommand::AddPointCommand(int pos, const QGeoCoordinate &point, RouteTableModel *model) :
    _pos(pos), _point(point), _model(model)
{
    _route = _model->currentRouteIndex();
}

int AddPointCommand::execute()
{
    _model->setCurrentRouteIndex(_route);
    _model->currentRouteChanged(_route);
    _model->insertPointToCurrentRoute(_pos, _point);
    return 0;
}

int AddPointCommand::unExecute()
{
    _model->setCurrentRouteIndex(_route);
    _model->currentRouteChanged(_route);
    RemovePointCommand command(_pos, _model);
    command.execute();
    return 0;
}

