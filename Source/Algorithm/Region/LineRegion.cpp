#include "LineRegion.h"
#include "../../Util/MathUtil.h"
#include "PointRegion.h"

using namespace psdf;

LineRegion::LineRegion(const Segment &segment) : Region(), mSegment(segment)
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

glm::dvec2 LineRegion::getDir() const
{
    glm::dvec2 edgeVector = getSegment().getEdgeVector();
    return edgeVector / glm::sqrt(glm::dot(edgeVector, edgeVector));
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
        glm::dvec2 dir = region.getDir();
        glm::dvec2 normal{dir.y, -dir.x};

        for (size_t j = 0; j < lineRegions.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            glm::dvec2 ba1 = pointRegions[j].getPoint() - point1;
            glm::dvec2 ba2 = pointRegions[j].getPoint() - point2;

            if (glm::dot(ba1, ba1) < CommonConstants::kEpsilon || glm::dot(ba2, ba2) < CommonConstants::kEpsilon ||
                glm::abs(glm::dot(normal, ba1)) < CommonConstants::kEpsilon || glm::abs(glm::dot(normal, ba2)) < CommonConstants::kEpsilon)
            {
                continue;
            }
            double t1 = glm::dot(ba1, ba1) / (2.0 * glm::dot(normal, ba1));
            double t2 = glm::dot(ba2, ba2) / (2.0 * glm::dot(normal, ba2));

            glm::dvec2 x = point1 + normal * t1;
            glm::dvec2 y = point2 + normal * t2;
            glm::dvec2 d = y - x;
            glm::dvec2 m{d.y, -d.x};
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

glm::dvec2 LineRegion::computeParabolics(const glm::dvec2 &point, const glm::dvec2 &normal, const glm::dvec2 &bPoint)
{
    glm::dvec2 d = bPoint - point;
    if (glm::abs(glm::dot(-d, -d)) < CommonConstants::kEpsilon)
    {
        return (point + bPoint) / 2.0;
    }
    else
    {
        return glm::dot(d, d) / (2 * glm::dot(normal, d)) * normal + point;
    }
}

glm::dvec2 LineRegion::computeBisectorIntersection(const glm::dvec2 &point, const glm::dvec2 &normal,
                                                   const glm::dvec2 &bPoint, const glm::dvec2 &bNormal,
                                                   const glm::dvec2 &g, bool isParallel)
{
    if (isParallel)
    {
        return 0.5 * dot(bPoint - point, normal) * normal + point;
    }
    else
    {
        auto a = dot(point - g, bNormal);
        auto b = (1 - dot(normal, bNormal));
        auto c = a / b * normal;
        return c + point;
    }
}

void LineRegion::cutWithLines(std::vector<LineRegion> &lineRegions)
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
        glm::dvec2 dir = region.getDir();
        glm::dvec2 normal{dir.y, -dir.x};

        for (size_t j = 0; j < lineRegions.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            LineRegion &bRegion = lineRegions[j];
            glm::dvec2 bPoint1 = bRegion.getSegment().getPoint2();
            glm::dvec2 bPoint2 = bRegion.getSegment().getPoint1(); // the points are flipped on purpose
            glm::dvec2 bDir = -bRegion.getDir();

            if (glm::dot(dir, point1 - bPoint1) * glm::sqrt(glm::dot(point1 - bPoint2, point1 - bPoint2)) <
                glm::dot(dir, point1 - bPoint2) * glm::sqrt(glm::dot(point1 - bPoint1, point1 - bPoint1)))
            {
                continue;
            }
            glm::dvec2 bNormal{-bDir.y, bDir.x};
            bool isParallel = glm::abs(glm::dot(dir, bNormal)) <= CommonConstants::kEpsilon;
            if (isParallel && glm::abs(glm::dot(bPoint1 - point1, normal)) < CommonConstants::kEpsilon)
            {
                continue;
            }

            glm::dvec2 g;
            if (isParallel)
            {
                g = (point1 + point2 + bPoint1 + bPoint2) / 4.0;
            }
            else
            {
                g = (glm::dot(bPoint1 - point1, bNormal) / glm::dot(dir, bNormal)) * dir + point1;
            }

            double ga1 = glm::dot(g - point1, dir);
            double ga2 = glm::dot(g - point2, dir);
            double gb1 = glm::dot(g - bPoint1, bDir);
            double gb2 = glm::dot(g - bPoint2, bDir);

            if (MathUtil::isMonotonic<double, 4>({ga1, ga2, gb1, gb2}, CommonConstants::kEpsilon) ||
                MathUtil::isMonotonic<double, 4>({gb1, gb2, ga1, ga2}, CommonConstants::kEpsilon))
            {
                continue;
            }

            glm::dvec2 x, y;
            if (MathUtil::isMonotonic<double, 3>({ga1, gb1, ga2}, CommonConstants::kEpsilon))
            {
                x = LineRegion::computeParabolics(point1, normal, bPoint1);
            }
            else
            {
                x = LineRegion::computeBisectorIntersection(point1, normal, bPoint1, bNormal, g, isParallel);
            }
            if (MathUtil::isMonotonic<double, 3>({ga1, gb2, ga2}, CommonConstants::kEpsilon))
            {
                y = LineRegion::computeParabolics(point2, normal, bPoint2);
            }
            else
            {
                y = LineRegion::computeBisectorIntersection(point2, normal, bPoint2, bNormal, g, isParallel);
            }

            glm::dvec2 d = y - x;
            glm::dvec2 m{d.y, -d.x};
            if (glm::dot(m, y - point1) + glm::dot(m, x - point2) < 0)
            {
                m = -m;
            }

            points.emplace_back(x);
            edgeVectors.emplace_back(m);
        }
        region.polyCut(points, edgeVectors);
    }
}
