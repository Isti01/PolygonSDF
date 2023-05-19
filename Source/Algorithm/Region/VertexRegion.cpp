#include "VertexRegion.h"
#include "../../CommonConstants.h"
#include "../../Util/CoordinateUtil.h"

using namespace psdf;

VertexRegion::VertexRegion(Vertex vertex, double cornerSign, size_t subdivisions, double initialBoundScale)
    : Region(initialBoundScale), mVertex(vertex), mCornerSign(cornerSign), mSubdivisions(subdivisions)
{
}

VertexRegion::VertexRegion(std::vector<glm::dvec2> bounds, Vertex vertex, double cornerSign, size_t subdivisions)
    : Region(std::move(bounds)), mVertex(vertex), mCornerSign(cornerSign), mSubdivisions(subdivisions)
{
}

void VertexRegion::cutWithVertices(std::vector<VertexRegion> &vertexRegions,
                                   const std::vector<VertexRegion> &cuttingRegions)
{
    if (vertexRegions.empty() || cuttingRegions.empty())
    {
        return;
    }
    std::vector<Vertex> vertices;
    vertices.reserve(vertexRegions.size() - 1);
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(vertexRegions.size() - 1);
    for (auto &region : vertexRegions)
    {
        vertices.clear();
        edgeVectors.clear();
        for (const auto &cuttingRegion : cuttingRegions)
        {
            glm::dvec2 edgeVector = cuttingRegion.mVertex - region.mVertex;
            if (glm::dot(edgeVector, edgeVector) < CommonConstants::kEpsilon)
            {
                continue;
            }

            vertices.emplace_back((cuttingRegion.mVertex + region.mVertex) / 2.0);
            edgeVectors.emplace_back(edgeVector);
        }
        region.polyCut(vertices, edgeVectors);
    }
}

void VertexRegion::cutWithEdges(std::vector<VertexRegion> &vertexRegions, const std::vector<EdgeRegion> &edgeRegions)
{
    if (vertexRegions.empty() || edgeRegions.empty())
    {
        return;
    }
    if (vertexRegions.empty() || edgeRegions.empty())
    {
        return;
    }
    std::vector<Vertex> vertices;
    vertices.reserve(vertexRegions.size() * (vertexRegions[0].mSubdivisions - 3));
    std::vector<glm::dvec2> edgeVectors;
    edgeVectors.reserve(vertexRegions.size() * (vertexRegions[0].mSubdivisions - 3));
    for (auto &region : vertexRegions)
    {
        vertices.clear();
        edgeVectors.clear();
        Vertex vertex = region.getVertex();
        for (const auto &lineRegion : edgeRegions)
        {
            const Vertex &segmentPoint1 = lineRegion.getEdge().getVertex1();
            const Vertex &segmentPoint2 = lineRegion.getEdge().getVertex2();

            glm::dvec2 edgeVector1 = segmentPoint1 - vertex;
            glm::dvec2 edgeVector2 = segmentPoint2 - vertex;
            if (glm::dot(edgeVector1, edgeVector1) < CommonConstants::kEpsilon ||
                glm::dot(edgeVector2, edgeVector2) < CommonConstants::kEpsilon)
            {
                continue;
            }

            for (int32_t steps = 1; steps < region.mSubdivisions - 2; steps++)
            {
                double t = steps / double(region.mSubdivisions - 1);
                glm::dvec2 nx = edgeVector1 + (segmentPoint2 - segmentPoint1) * t;
                vertices.emplace_back(vertex + nx / 2.0);
                edgeVectors.emplace_back(nx);
            }
        }
        region.polyCut(vertices, edgeVectors);
    }
}

Vertex VertexRegion::getVertex() const
{
    return mVertex;
}

double VertexRegion::getCornerSign() const
{
    return mCornerSign;
}

double VertexRegion::getDistanceToPointInsideBounds(Vertex vertex) const
{
    return glm::distance(vertex, mVertex) * mCornerSign;
}

void VertexRegion::createMesh(std::vector<VertexRegionBoundVertex> &vertices, std::vector<uint32_t> &indices,
                              Vertex fanCenter) const
{
    if (mBounds.empty())
    {
        return;
    }
    size_t initialVertexCount = vertices.size();

    for (const auto &boundVertex : mBounds)
    {
        vertices.push_back(
            {mVertex, float2(boundVertex), static_cast<float>(getDistanceToPointInsideBounds(boundVertex))});
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
