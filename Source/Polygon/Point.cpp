#include "Point.h"

using namespace psdf;

Point::Point(Falcor::float2 coordinates) : mCoordinates(coordinates)
{
}

Falcor::float2 Point::getCoordinates() const
{
    return mCoordinates;
}
