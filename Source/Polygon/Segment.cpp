#include "Segment.h"

using namespace psdf;

Segment::Segment(const Segment::Endpoints &endpoints) : mEndpoints(endpoints)
{
}

Segment::Endpoints Segment::getEndpoints() const
{
    return mEndpoints;
}

float2 Segment::getEdgeVector() const
{
    return mEndpoints[1] - mEndpoints[0];
}

Point Segment::getPoint1() const
{
    return mEndpoints[0];
}

Point Segment::getPoint2() const
{
    return mEndpoints[1];
}
