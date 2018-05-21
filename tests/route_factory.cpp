#include "route_factory.h"

RouteFactory::RouteFactory()
{

}

shared_ptr<Route> RouteFactory::create(const RouteData &data)
{
    shared_ptr<Route> route = make_shared<Route>();
    route->setName(data.name);
    route->setDistance(data.distance);
    route->setDate(data.date);
    return route;
}
