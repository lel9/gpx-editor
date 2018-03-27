#ifndef EDITPOINTCOMMAND_H
#define EDITPOINTCOMMAND_H

#include "command.h"
#include "route.h"

class EditPointCommand : public Command
{
private:
    int _pos;
    QGeoCoordinate _oldPoint;
    QGeoCoordinate _newPoint;
    shared_ptr<Route> _route;

public:
    EditPointCommand(int pos, const QGeoCoordinate &newPoint, const shared_ptr<Route> &route);
    ~EditPointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // EDITPOINTCOMMAND_H
