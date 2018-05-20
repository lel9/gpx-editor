#include "remove_point_command.h"
#include "add_point_command.h"

RemovePointCommand::RemovePointCommand(int pos, RouteTableModel *model) :
    _pos(pos), _model(model)
{
    _route = _model->currentRouteIndex();
}

int RemovePointCommand::execute()
{
    try
    {
        _model->setCurrentRouteIndex(_route);
        _model->currentRouteChanged(_route);
        _point = _model->removePointFromCurrentRoute(_pos);
    }
    catch (std::exception &)
    {
        return 1;
    }
    return 0;
}

int RemovePointCommand::unExecute()
{
    _model->setCurrentRouteIndex(_route);
    _model->currentRouteChanged(_route);
    AddPointCommand command(_pos, _point, _model);
    command.execute();
    return 0;
}

