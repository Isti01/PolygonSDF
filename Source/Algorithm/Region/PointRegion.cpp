#include "PointRegion.h"
#include "../../CommonConstants.h"
#include "../../Util/CoordinateUtil.h"

using namespace psdf;

PointRegion::PointRegion(Point point, double cornerSign, size_t subdivisions, double initialBoundScale)
    : Region(initialBoundScale), mPoint(point), mCornerSign(cornerSign), mSubdivisions(subdivisions)
{
}

PointRegion::PointRegion(std::vector<glm::dvec2> bounds, Point point, double cornerSign, size_t subdivisions)
    : Region(std::move(bounds)), mPoint(point), mCornerSign(cornerSign), mSubdivisions(subdivisions)
{
}

void PointRegion::cutWithPoints(std::vector<PointRegion> &pointRegions, const std::vector<PointRegion> &cuttingRegions)
{
    if (pointRegions.empty() || cuttingRegions.empty())
    {
        return;
    }
    std::vector<Point> points;
    points.reserve(pointRegions.size() - 1);
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(pointRegions.size() - 1);
    for (auto &region : pointRegions)
    {
        points.clear();
        edgeVectors.clear();
        for (const auto &cuttingRegion : cuttingRegions)
        {
            glm::dvec2 edgeVector = cuttingRegion.mPoint - region.mPoint;
            if (glm::dot(edgeVector, edgeVector) < CommonConstants::kEpsilon)
            {
                continue;
            }

            points.emplace_back((cuttingRegion.mPoint + region.mPoint) / 2.0);
            edgeVectors.emplace_back(edgeVector);
        }
        region.polyCut(points, edgeVectors);
    }
}

void PointRegion::cutWithLines(std::vector<PointRegion> &pointRegions, const std::vector<LineRegion> &lineRegions)
{
    if (pointRegions.empty() || lineRegions.empty())
    {
        return;
    }
    if (pointRegions.empty() || lineRegions.empty())
    {
        return;
    }
    std::vector<Point> points;
    points.reserve(pointRegions.size() * (pointRegions[0].mSubdivisions - 3));
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(pointRegions.size() * (pointRegions[0].mSubdivisions - 3));
    for (auto &region : pointRegions)
    {
        points.clear();
        edgeVectors.clear();
        Point point = region.getPoint();
        for (const auto &lineRegion : lineRegions)
        {
            const Point &segmentPoint1 = lineRegion.getSegment().getPoint1();
            const Point &segmentPoint2 = lineRegion.getSegment().getPoint2();

            glm::dvec2 edgeVector1 = segmentPoint1 - point;
            glm::dvec2 edgeVector2 = segmentPoint2 - point;
            if (glm::dot(edgeVector1, edgeVector1) < CommonConstants::kEpsilon ||
                glm::dot(edgeVector2, edgeVector2) < CommonConstants::kEpsilon)
            {
                continue;
            }

            for (int32_t steps = 1; steps < region.mSubdivisions - 2; steps++)
            {
                double t = steps / double(region.mSubdivisions - 1);
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

double PointRegion::getDistanceToPointInsideBounds(Point point) const
{
    return glm::distance(point, mPoint) * mCornerSign;
}

void PointRegion::createMesh(std::vector<PointRegionBoundVertex> &vertices, std::vector<uint32_t> &indices,
                             Point fanCenter) const
{
    if (mBounds.empty())
    {
        return;
    }
    size_t initialVertexCount = vertices.size();

    for (const auto &boundVertex : mBounds)
    {
        vertices.push_back(
            {mPoint, float2(boundVertex), static_cast<float>(getDistanceToPointInsideBounds(boundVertex))});
    }
    std::optional<size_t> centerIndexOptional = CoordinateUtil::findClosestInSubPolygon(mBounds, fanCenter);
    FALCOR_ASSERT(centerIndexOptional);
    size_t centerIndex = *centerIndexOptional;

    for (size_t i = 0; i < mBounds.size() - 2; i++)
    {
        indices.push_back(initialVertexCount + centerIndex);
        indices.push_back(initialVertexCount + ((centerIndex + i + 1) % mBounds.size()));
        indices.push_back(initialVertexCount + ((centerIndex + i + 2) % mBounds.size()));
    }
}
