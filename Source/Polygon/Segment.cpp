#include "Segment.h"

using namespace psdf;

Segment::Segment(const Segment::Endpoints &endpoints) : mEndpoints(endpoints)
{
}

Segment::Endpoints Segment::getEndpoints() const
{
    return mEndpoints;
}
