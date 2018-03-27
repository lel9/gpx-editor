#ifndef ADDPOINTBEFORECOMMAND_H
#define ADDPOINTBEFORECOMMAND_H

#include "command.h"
#include "route.h"

class AddPointCommand : public Command
{
private:
    int _pos;
    shared_ptr<Route> _route;
    QGeoCoordinate _point;
public:
    AddPointCommand(int pos, const shared_ptr<Route> &route);
    AddPointCommand(int pos, const shared_ptr<Route> &route, const QGeoCoordinate &point);
    ~AddPointCommand() = default;

    virtual int execute() override;
    virtual int unExecute() override;
};

#endif // ADDPOINTBEFORECOMMAND_H
