#ifndef ROUTEFACTORY_H
#define ROUTEFACTORY_H

#include "../../src/route.h"
#include "../../tests/data_struct.h"

class RouteFactory
{
public:
    RouteFactory();
    static shared_ptr<Route> create(const RouteData &data);
};

#endif // ROUTEFACTORY_H
