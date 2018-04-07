#include "add_route_command.h"
#include "remove_route_command.h"

AddRouteCommand::AddRouteCommand(RouteTableModel *model) :
    _model(model)
{
    _pos = _model->rowCount();
    _route = make_shared<Route>();
}

AddRouteCommand::AddRouteCommand(int pos, const shared_ptr<Route> &route,
                                 RouteTableModel *model) :
    _pos(pos), _route(route), _model(model)
{
}

int AddRouteCommand::execute()
{
    _model->insertRoute(_pos, _route);
    return 0;
}

int AddRouteCommand::unExecute()
{
    RemoveRouteCommand command(_pos, _model);
    command.execute();
    return 0;
}
