#include "LineRegion.h"

using namespace psdf;

LineRegion::LineRegion(const Segment &segment) : mSegment(segment)
{
}

LineRegion::LineRegion(std::vector<glm::dvec2> bounds, const Segment &segment)
    : Region(std::move(bounds)), mSegment(segment)
{
}

Segment LineRegion::getSegment() const
{
    return mSegment;
}
