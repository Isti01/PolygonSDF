#include "Polygon.h"

#include <utility>

using namespace psdf;

Polygon::Polygon(Polygon::Points points, Polygon::Segments segments)
    : mPoints(std::move(points)), mSegments(std::move(segments))
{
}

Polygon::SharedPtr Polygon::create(const std::vector<Point> &points)
{
    FALCOR_ASSERT(points.size() > 2);
    auto segments = connectOrderedPoints(points);

    return std::shared_ptr<Polygon>(new Polygon(points, segments));
}

Polygon::Segments Polygon::connectOrderedPoints(const std::vector<Point> &points)
{
    std::vector<Segment> segments;
    segments.reserve(points.size());

    for (int32_t i = 0; i < points.size(); i++)
    {
        segments.emplace_back(Segment{{points[i], points[(i + 1) % points.size()]}});
    }

    return segments;
}

Polygon::Points Polygon::getPoints() const
{
    return mPoints;
}

Polygon::Segments Polygon::getSegments() const
{
    return mSegments;
}
