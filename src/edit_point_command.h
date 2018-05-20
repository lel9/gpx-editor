#ifndef EDITPOINTCOMMAND_H
#define EDITPOINTCOMMAND_H

#include "command.h"
#include "route_table_model.h"
#include "table_index.h"

class EditPointCommand : public Command
{
private:
    int _pos;
    QGeoCoordinate _point;
    QGeoCoordinate _oldPoint;
    int _route;
    RouteTableModel *_model;

public:
    EditPointCommand(const TableIndex &index, double val, RouteTableModel *model);
    ~EditPointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // EDITPOINTCOMMAND_H
