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
    for (size_t j = 0; j < pointRegions.size(); j++)
    {
        points.clear();
        edgeVectors.clear();
        PointRegion &region = pointRegions[j];

        for (size_t i = 0; i < pointRegions.size(); i++)
        {
            if (j == i)
            {
                continue;
            }

            glm::dvec2 edgeVector = pointRegions[i].mPoint - region.mPoint;
            if (glm::dot(edgeVector, edgeVector) < Region::Epsilon)
            {
                continue;
            }

            points.emplace_back((pointRegions[i].mPoint + region.mPoint) / 2.0);
            edgeVectors.emplace_back(edgeVector);
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
