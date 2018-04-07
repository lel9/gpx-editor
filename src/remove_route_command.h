#ifndef REMOVEROUTECOMMAND_H
#define REMOVEROUTECOMMAND_H

#include "command.h"
#include "route_table_model.h"

class RemoveRouteCommand : public Command
{
private:
    int _pos;
    shared_ptr<Route> _route;
    RouteTableModel *_model;

public:
    RemoveRouteCommand(int pos, RouteTableModel *model);
    ~RemoveRouteCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // REMOVEROUTECOMMAND_H
