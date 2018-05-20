#ifndef RANDOMROUTEFACTORY_H
#define RANDOMROUTEFACTORY_H

#include "../../src/route.h"
class RandomRouteFactory
{
public:
    RandomRouteFactory();
    static shared_ptr<Route> create(int pointCount);
};

#endif // RANDOMROUTEFACTORY_H
