#include "remove_point_command.h"
#include "add_point_command.h"

RemovePointCommand::RemovePointCommand(int pos, const shared_ptr<Route> &route) :
    _pos(pos), _route(route)
{
}

int RemovePointCommand::execute()
{
    try
    {
        _point = _route->removePoint(_pos);
    }
    catch (std::exception &)
    {
        return 1;
    }
    return 0;
}

int RemovePointCommand::unExecute()
{
    AddPointCommand command(_pos, _route, _point);
    command.execute();
    return 0;
}

