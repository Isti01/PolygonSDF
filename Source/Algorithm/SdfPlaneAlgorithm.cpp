#include "SdfPlaneAlgorithm.h"

using namespace psdf;

static bool isCcwWindingOrder(const SubPolygon &subPolygon)
{
    double sum = 0;
    const SubPolygon::Points &points = subPolygon.getPoints();
    size_t pointsSize = points.size();
    for (size_t i = 0; i < pointsSize; i++)
    {
        Point point1 = points[i];
        Point point2 = points[(i + 1) % pointsSize];
        sum += (point2.x - point1.x) * (point2.y + point1.y);
    }

    return sum < 0;
}

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithm::calculateForPolygon(const Polygon::SharedPtr &pPolygon)
{
    std::vector<LineRegion> lineRegions;
    std::vector<PointRegion> pointRegions;

    std::vector<SubPolygon> reorderedPolygons = pPolygon->getPolygons();

    for (auto &subPolygon : reorderedPolygons)
    {
        if (!isCcwWindingOrder(subPolygon))
        {
            continue;
        }
        SubPolygon::Points pointsCopy = subPolygon.getPoints();
        std::reverse(pointsCopy.begin(), pointsCopy.end());
        subPolygon = SubPolygon(std::move(pointsCopy));
    }

    for (const auto &subPolygon : reorderedPolygons)
    {
        const std::vector<Segment> &segments = subPolygon.getSegments();

        size_t size = segments.size();
        for (int i = 0; i < size; i++)
        {
            Segment segment1 = segments[i];
            Segment segment2 = segments[(i + 1) % size];

            glm::dvec2 edgeVector1 = segment1.getEdgeVector();
            glm::dvec2 edgeVector2 = segment2.getEdgeVector();
            double cornerSign = glm::sign(glm::dot(glm::dvec2{-edgeVector1.y, edgeVector1.x}, edgeVector2));

            lineRegions.emplace_back(segment1);
            lineRegions.back().polyCut({segment1.getPoint2(), segment1.getPoint1()}, {edgeVector1, -edgeVector1});
            pointRegions.emplace_back(segment1.getPoint2(), cornerSign);
            pointRegions.back().polyCut({segment1.getPoint2(), segment1.getPoint2()}, {edgeVector2, -edgeVector1});
        }
    }

    PointRegion::cutWithPoints(pointRegions);
    PointRegion::cutWithLines(pointRegions, lineRegions);

    LineRegion::cutWithPoints(lineRegions, pointRegions);
    LineRegion::cutWithLines(lineRegions);

    return SdfPlaneAlgorithmOutput::create(pointRegions, lineRegions);
}
