#include "PointRegion.h"

using namespace psdf;

PointRegion::PointRegion(Point point, double cornerSign) : mPoint(point), mCornerSign(cornerSign)
{
}

PointRegion::PointRegion(std::vector<glm::dvec2> bounds, Point point, double cornerSign)
    : Region(std::move(bounds)), mPoint(point), mCornerSign(cornerSign)
{
}

void PointRegion::cutWithPoints(std::vector<PointRegion> &pointRegions)
{
    std::vector<Point> points;
    points.reserve(pointRegions.size() - 1);
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(pointRegions.size() - 1);
    for (size_t i = 0; i < pointRegions.size(); i++)
    {
        points.clear();
        edgeVectors.clear();
        PointRegion &region = pointRegions[i];

        for (size_t j = 0; j < pointRegions.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            glm::dvec2 edgeVector = pointRegions[j].mPoint - region.mPoint;
            if (glm::dot(edgeVector, edgeVector) < Region::kEpsilon)
            {
                continue;
            }

            points.emplace_back((pointRegions[j].mPoint + region.mPoint) / 2.0);
            edgeVectors.emplace_back(edgeVector);
        }
        region.polyCut(points, edgeVectors);
    }
}

void PointRegion::cutWithLines(std::vector<PointRegion> &pointRegions, const std::vector<LineRegion> &lineRegions)
{
    std::vector<Point> points;
    points.reserve(pointRegions.size() * (kSubDivs - 3));
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(pointRegions.size() * (kSubDivs - 3));
    for (size_t i = 0; i < pointRegions.size(); i++)
    {
        points.clear();
        edgeVectors.clear();
        PointRegion &region = pointRegions[i];
        Point point = region.getPoint();
        for (size_t j = 0; j < pointRegions.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            const LineRegion &lineRegion = lineRegions[j];
            const Point &segmentPoint1 = lineRegion.getSegment().getPoint1();
            const Point &segmentPoint2 = lineRegion.getSegment().getPoint2();

            glm::dvec2 edgeVector1 = segmentPoint1 - point;
            glm::dvec2 edgeVector2 = segmentPoint2 - point;
            if (glm::dot(edgeVector1, edgeVector1) < Region::kEpsilon ||
                glm::dot(edgeVector2, edgeVector2) < Region::kEpsilon)
            {
                continue;
            }

            for (int32_t steps = 1; steps < kSubDivs - 2; steps++)
            {
                double t = steps / double(kSubDivs - 1);
                glm::dvec2 nx = edgeVector1 + (segmentPoint2 - segmentPoint1) * t;
                points.emplace_back(point + nx / 2.0);
                edgeVectors.emplace_back(nx);
            }
        }
        region.polyCut(points, edgeVectors);
    }
}

Point PointRegion::getPoint() const
{
    return mPoint;
}

double PointRegion::getCornerSign() const
{
    return mCornerSign;
}
