#ifndef REMOVE_POINT_COMMAND_H
#define REMOVE_POINT_COMMAND_H

#include "command.h"
#include "route.h"

class RemovePointCommand : public Command
{
private:
    int _pos;
    shared_ptr<Route> _route;
    QGeoCoordinate _point;

public:
    RemovePointCommand(int pos, const shared_ptr<Route> &route);
    ~RemovePointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // REMOVE_POINT_COMMAND_H
