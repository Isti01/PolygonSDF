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

static bool isSubPolygonInside(size_t polygonIndex, const std::vector<SubPolygon> &polygons)
{
    bool isInside = false;

    // checking only one of the points is enough, because we don't work with self-intersecting polygons
    glm::dvec2 coordToCheck = polygons[polygonIndex].getPoints()[0];

    for (size_t j = 0; j < polygons.size(); j++)
    {
        if (j == polygonIndex)
        {
            continue;
        }

        for (const auto &segment : polygons[j].getSegments())
        {
            glm::dvec2 e = segment.getPoint1() - segment.getPoint2();
            glm::dvec2 w = coordToCheck - segment.getPoint2();
            glm::bvec3 winding{
                coordToCheck.y >= segment.getPoint2().y,
                coordToCheck.y<segment.getPoint1().y, e.x * w.y> e.y * w.x,
            };
            if (all(winding) || all(glm::not_(winding)))
            {
                isInside = !isInside;
            }
        }
    }
    return isInside;
}

static void reorderPointsForTheAlgorithm(std::vector<SubPolygon> &reorderedPolygons)
{
    for (size_t i = 0; i < reorderedPolygons.size(); i++)
    {
        auto &subPolygon = reorderedPolygons[i];
        bool isPolygonCcWindingOrder = isCcwWindingOrder(subPolygon);
        bool isOnInside = isSubPolygonInside(i, reorderedPolygons);
        if (isOnInside && isPolygonCcWindingOrder || (!isOnInside && !isPolygonCcWindingOrder))
        {
            SubPolygon::Points pointsCopy = subPolygon.getPoints();
            std::reverse(pointsCopy.begin(), pointsCopy.end());
            subPolygon = SubPolygon(std::move(pointsCopy));
        }
    }
}

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithm::calculateForPolygon(const Polygon::SharedPtr &pPolygon)
{
    std::vector<LineRegion> lineRegions;
    std::vector<PointRegion> pointRegions;

    std::vector<SubPolygon> reorderedPolygons = pPolygon->getPolygons();
    reorderPointsForTheAlgorithm(reorderedPolygons);

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
