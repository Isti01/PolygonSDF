#include "Polygon.h"

#include <utility>

using namespace psdf;

Polygon::SharedPtr Polygon::kExamplePolygon = Polygon::create({{.5, 0}, {0, .5}, {-.5, 0}, {0, -.5}});

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

Polygon::FloatPoints psdf::Polygon::getFloatPoints() const
{
    FloatPoints points;
    points.reserve(mPoints.size());
    std::copy(mPoints.cbegin(), mPoints.cend(), std::back_inserter(points));
    return points;
}

Polygon::FloatSegments psdf::Polygon::getFloatSegments() const
{
    FloatSegments segments;
    segments.reserve(mSegments.size());
    std::transform(mSegments.cbegin(), mSegments.cend(), std::back_inserter(segments), [](const Segment& segment) {
        return std::array<float2, 2>{{segment.getPoint1(), segment.getPoint2()}};
    });
    return segments;
}
