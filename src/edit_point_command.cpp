#include "edit_point_command.h"

EditPointCommand::EditPointCommand(int pos, const QGeoCoordinate &newPoint,
                                   const shared_ptr<Route> &route) :
    _pos(pos), _newPoint(newPoint), _route(route)
{
}

int EditPointCommand::execute()
{
    try
    {
        _oldPoint = _route->replacePoint(_pos, _newPoint);
    }
    catch (std::exception &)
    {
        return 1;
    }

    return 0;
}

int EditPointCommand::unExecute()
{
    try
    {
        _route->replacePoint(_pos, _oldPoint);
    }
    catch (std::exception &)
    {
        return 1;
    }
    return 0;
}

