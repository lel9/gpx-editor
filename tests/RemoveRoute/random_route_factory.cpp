#include "random_route_factory.h"
#include <ctime>

RandomRouteFactory::RandomRouteFactory()
{

}

shared_ptr<Route> RandomRouteFactory::create(int pointCount)
{
    srand(time(0));
    shared_ptr<Route> route = make_shared<Route>();
    for (int j = 0; j < pointCount; j++)
        route->appendPoint(QGeoCoordinate(-90 + rand() % 181, -180 + rand() % 361));
    return route;
}

