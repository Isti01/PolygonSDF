#include "Polygon.h"

#include <utility>

using namespace psdf;

Polygon::Polygon(Polygon::Points points, Polygon::Segments segments)
    : mpPoints(std::move(points)), mpSegments(std::move(segments))
{
}

Polygon::SharedPtr Polygon::create(const std::vector<Point> &points)
{
    FALCOR_ASSERT(points.size() > 2);
    auto mpPoints = std::make_shared<std::vector<Point>>(points);
    auto mpSegments = connectOrderedPoints(points);

    return std::shared_ptr<Polygon>(new Polygon(mpPoints, mpSegments));
}

Polygon::Segments Polygon::connectOrderedPoints(const std::vector<Point> &points)
{
    auto segments = std::make_shared<std::vector<Segment>>();
    segments->reserve(points.size());

    for (int32_t i = 0; i < points.size(); i++)
    {
        segments->push_back({{points[i], points[(i + 1) % points.size()]}});
    }

    return segments;
}

Polygon::Points Polygon::getPoints() const
{
    return mpPoints;
}

Polygon::Segments Polygon::getSegments() const
{
    return mpSegments;
}
