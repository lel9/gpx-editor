#include "add_point_command.h"
#include "remove_point_command.h"

AddPointCommand::AddPointCommand(int pos, const shared_ptr<Route> &route) :
    _pos(pos), _route(route), _point(0, 0)
{
}

AddPointCommand::AddPointCommand(int pos, const shared_ptr<Route> &route,
                                 const QGeoCoordinate &point) :
    _pos(pos), _route(route), _point(point)
{
}

int AddPointCommand::execute()
{
    _route->insertPoint(_pos, _point);
    return 0;
}

int AddPointCommand::unExecute()
{
    RemovePointCommand command(_pos, _route);
    command.execute();
    return 0;
}

