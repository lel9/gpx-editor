#ifndef ADDPOINTBEFORECOMMAND_H
#define ADDPOINTBEFORECOMMAND_H

#include "command.h"
#include "route_table_model.h"

class AddPointCommand : public Command
{
private:
    int _pos;
    QGeoCoordinate _point;
    int _route;
    RouteTableModel *_model;
public:
    AddPointCommand(int pos, RouteTableModel *model);
    AddPointCommand(int pos, const QGeoCoordinate &point, RouteTableModel *model);
    ~AddPointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // ADDPOINTBEFORECOMMAND_H
