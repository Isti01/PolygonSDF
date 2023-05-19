#include "EdgeRegion.h"
#include "../../CommonConstants.h"
#include "../../Util/CoordinateUtil.h"
#include "../../Util/MathUtil.h"
#include "VertexRegion.h"

using namespace psdf;

EdgeRegion::EdgeRegion(const Edge &edge, double initialBoundScale) : Region(initialBoundScale), mEdge(edge)
{
}

EdgeRegion::EdgeRegion(std::vector<glm::dvec2> bounds, Edge edge) : Region(std::move(bounds)), mEdge(std::move(edge))
{
}

Edge EdgeRegion::getEdge() const
{
    return mEdge;
}

glm::dvec2 EdgeRegion::getDir() const
{
    glm::dvec2 edgeVector = getEdge().getEdgeVector();
    return edgeVector / glm::sqrt(glm::dot(edgeVector, edgeVector));
}

void EdgeRegion::cutWithVertices(std::vector<EdgeRegion> &edgeRegions, const std::vector<VertexRegion> &vertexRegions)
{
    if (vertexRegions.empty() || edgeRegions.empty())
    {
        return;
    }
    std::vector<Vertex> points;
    points.reserve(edgeRegions.size() - 1);
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(edgeRegions.size() - 1);
    for (auto &region : edgeRegions)
    {
        points.clear();
        edgeVectors.clear();
        Vertex point1 = region.getEdge().getVertex1();
        Vertex point2 = region.getEdge().getVertex2();
        glm::dvec2 dir = region.getDir();
        glm::dvec2 normal{dir.y, -dir.x};

        for (const auto &pointRegion : vertexRegions)
        {
            glm::dvec2 ba1 = pointRegion.getVertex() - point1;
            glm::dvec2 ba2 = pointRegion.getVertex() - point2;

            if (glm::dot(ba1, ba1) < CommonConstants::kEpsilon || glm::dot(ba2, ba2) < CommonConstants::kEpsilon ||
                glm::abs(glm::dot(normal, ba1)) < CommonConstants::kEpsilon ||
                glm::abs(glm::dot(normal, ba2)) < CommonConstants::kEpsilon)
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

glm::dvec2 EdgeRegion::computeParabolics(const glm::dvec2 &point, const glm::dvec2 &normal, const glm::dvec2 &bPoint)
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

glm::dvec2 EdgeRegion::computeBisectorIntersection(const glm::dvec2 &point, const glm::dvec2 &normal,
                                                   const glm::dvec2 &bPoint, const glm::dvec2 &bNormal,
                                                   const glm::dvec2 &g, bool isParallel)
{
    if (isParallel)
    {
        return 0.5 * dot(bPoint - point, normal) * normal + point;
    }
    else
    {
        return dot(point - g, bNormal) / (1 - dot(normal, bNormal)) * normal + point;
    }
}

void EdgeRegion::cutWithEdges(std::vector<EdgeRegion> &edgeRegions, const std::vector<EdgeRegion> &cuttingRegions)
{
    if (edgeRegions.empty() || cuttingRegions.empty())
    {
        return;
    }
    std::vector<Vertex> points;
    points.reserve(edgeRegions.size() - 1);
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(edgeRegions.size() - 1);
    for (auto &region : edgeRegions)
    {
        points.clear();
        edgeVectors.clear();
        Vertex point1 = region.getEdge().getVertex1();
        Vertex point2 = region.getEdge().getVertex2();
        glm::dvec2 dir = region.getDir();
        glm::dvec2 normal{dir.y, -dir.x};

        for (const auto &bRegion : cuttingRegions)
        {
            glm::dvec2 bPoint1 = bRegion.getEdge().getVertex2();
            glm::dvec2 bPoint2 = bRegion.getEdge().getVertex1(); // the points are flipped on purpose
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
                x = EdgeRegion::computeParabolics(point1, normal, bPoint1);
            }
            else
            {
                x = EdgeRegion::computeBisectorIntersection(point1, normal, bPoint1, bNormal, g, isParallel);
            }
            if (MathUtil::isMonotonic<double, 3>({ga1, gb2, ga2}, CommonConstants::kEpsilon))
            {
                y = EdgeRegion::computeParabolics(point2, normal, bPoint2);
            }
            else
            {
                y = EdgeRegion::computeBisectorIntersection(point2, normal, bPoint2, bNormal, g, isParallel);
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

double EdgeRegion::getDistanceToPointInsideBounds(Vertex point) const
{
    glm::dvec2 dir = getDir();
    glm::dvec2 normal{-dir.y, dir.x};
    return -glm::dot(point - getEdge().getVertex1(), normal);
}

void EdgeRegion::createMesh(std::vector<EdgeRegionBoundVertex> &vertices, std::vector<uint32_t> &indices,
                            Vertex fanCenter) const
{
    if (mBounds.empty())
    {
        return;
    }
    size_t initialVertexCount = vertices.size();

    for (const auto &boundVertex : mBounds)
    {
        vertices.push_back({float2(boundVertex), static_cast<float>(getDistanceToPointInsideBounds(boundVertex))});
    }
    std::optional<size_t> centerIndexOptional = CoordinateUtil::findClosestInOutline(mBounds, fanCenter);
    FALCOR_ASSERT(centerIndexOptional);
    size_t centerIndex = *centerIndexOptional;

    for (size_t i = 0; i < mBounds.size() - 2; i++)
    {
        indices.push_back(initialVertexCount + centerIndex);
        indices.push_back(initialVertexCount + ((centerIndex + i + 1) % mBounds.size()));
        indices.push_back(initialVertexCount + ((centerIndex + i + 2) % mBounds.size()));
    }
}
