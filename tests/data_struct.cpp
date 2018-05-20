#include "data_struct.h"

bool operator ==(const RouteData &first, const RouteData &second)
{
    if (first.name != second.name)
        return false;
    if (first.distance != second.distance)
        return false;
    if (first.date != second.date)
        return false;
    return true;
}

bool operator !=(const RouteData &first, const RouteData &second)
{
    return !(first == second);
}

bool operator ==(const PointData &first, const PointData &second)
{
    if (first.lat != second.lat)
        return false;
    if (first.lon != second.lon)
        return false;
    if (first.alt != second.alt)
        return false;
    return true;
}

bool operator !=(const PointData &first, const PointData &second)
{
    return !(first == second);
}
