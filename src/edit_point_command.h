#ifndef EDITPOINTCOMMAND_H
#define EDITPOINTCOMMAND_H

#include "command.h"
#include "route_table_model.h"

class EditPointCommand : public Command
{
private:
    QModelIndex _index;
    double _val;
    double _oldVal;
    int _route;
    RouteTableModel *_model;

public:
    EditPointCommand(QModelIndex index, double val, RouteTableModel *model);
    ~EditPointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // EDITPOINTCOMMAND_H
