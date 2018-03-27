#include "remove_route_command.h"
#include "add_route_command.h"

RemoveRouteCommand::RemoveRouteCommand(int pos, const shared_ptr<RouteTableModel> &model) :
    _pos(pos), _model(model)
{
}

int RemoveRouteCommand::execute()
{ 
    try
    {
        _route = _model->removeRoute(_pos);
    }
    catch (std::exception &)
    {
        return 1;
    }

    return 0;
}

int RemoveRouteCommand::unExecute()
{
    AddRouteCommand command(_pos, _route, _model);
    command.execute();
    return 0;
}

