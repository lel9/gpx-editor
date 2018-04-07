#ifndef REMOVE_POINT_COMMAND_H
#define REMOVE_POINT_COMMAND_H

#include "command.h"
#include "route_table_model.h"

class RemovePointCommand : public Command
{
private:
    int _pos;
    RouteTableModel *_model;
    int _route;
    QGeoCoordinate _point;

public:
    RemovePointCommand(int pos, RouteTableModel *model);
    ~RemovePointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // REMOVE_POINT_COMMAND_H
