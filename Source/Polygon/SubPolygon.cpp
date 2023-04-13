#include "SubPolygon.h"

using namespace psdf;

SubPolygon::SubPolygon(SubPolygon::Points points) : mPoints(std::move(points)), mSegments(connectOrderedPoints(mPoints))
{
    FALCOR_ASSERT(mPoints.size() > 2);
}

SubPolygon::Points SubPolygon::getPoints() const
{
    return mPoints;
}

SubPolygon::Segments SubPolygon::getSegments() const
{
    return mSegments;
}

SubPolygon::FloatPoints SubPolygon::getFloatPoints() const
{
    FloatPoints points;
    points.reserve(mPoints.size());
    std::copy(mPoints.cbegin(), mPoints.cend(), std::back_inserter(points));
    return points;
}

SubPolygon::FloatSegments SubPolygon::getFloatSegments() const
{
    FloatSegments segments;
    segments.reserve(mSegments.size());
    std::transform(mSegments.cbegin(), mSegments.cend(), std::back_inserter(segments), [](const Segment &segment) {
        return std::array<float2, 2>{{segment.getPoint1(), segment.getPoint2()}};
    });
    return segments;
}

SubPolygon::Segments SubPolygon::connectOrderedPoints(const std::vector<Point> &points)
{
    std::vector<Segment> segments;
    segments.reserve(points.size());

    for (int32_t i = 0; i < points.size(); i++)
    {
        segments.emplace_back(Segment{{points[i], points[(i + 1) % points.size()]}});
    }

    return segments;
}
