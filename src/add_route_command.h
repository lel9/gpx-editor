#ifndef ADDROUTECOMMAND_H
#define ADDROUTECOMMAND_H

#include "command.h"
#include "route_table_model.h"

class AddRouteCommand : public Command
{
private:
    int _pos;
    shared_ptr<Route> _route;
    RouteTableModel *_model;

public:
    AddRouteCommand(RouteTableModel *model);
    AddRouteCommand(int pos, const shared_ptr<Route> &route, RouteTableModel *model);
    ~AddRouteCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // ADDROUTECOMMAND_H
