#include "LineRegion.h"
#include "PointRegion.h"

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

void LineRegion::cutWithPoints(std::vector<LineRegion> &lineRegions, const std::vector<PointRegion> &pointRegions)
{
    std::vector<Point> points;
    points.reserve(lineRegions.size() - 1);
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(lineRegions.size() - 1);
    for (size_t i = 0; i < lineRegions.size(); i++)
    {
        points.clear();
        edgeVectors.clear();
        LineRegion &region = lineRegions[i];
        Point point1 = region.getSegment().getPoint1();
        Point point2 = region.getSegment().getPoint2();
        glm::dvec2 edgeVector = region.getSegment().getEdgeVector();
        glm::dvec2 dir = edgeVector / glm::sqrt(glm::dot(edgeVector, edgeVector));
        glm::dvec2 normal{-dir.y, dir.x};

        for (size_t j = 0; j < lineRegions.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            glm::dvec2 ba1 = pointRegions[j].getPoint() - point1;
            glm::dvec2 ba2 = pointRegions[j].getPoint() - point2;

            if (glm::dot(ba1, ba1) < kEpsilon || glm::dot(ba2, ba2) < kEpsilon ||
                glm::abs(glm::dot(normal, ba1)) < kEpsilon || glm::abs(glm::dot(normal, ba2)) < kEpsilon)
            {
                continue;
            }
            double t1 = glm::dot(ba1, ba1) / (2.0 * glm::dot(normal, ba1));
            double t2 = glm::dot(ba2, ba2) / (2.0 * glm::dot(normal, ba2));

            glm::dvec2 x = point1 + normal * t1;
            glm::dvec2 y = point2 + normal * t2;
            glm::dvec2 d = y - x;
            glm::dvec2 m{-d.y, d.x};
            if (glm::dot(m, x - point1) < 0)
            {
                m *= -1;
            }

            points.emplace_back(x);
            edgeVectors.emplace_back(m);
        }
        region.polyCut(points, edgeVectors);
    }
}
