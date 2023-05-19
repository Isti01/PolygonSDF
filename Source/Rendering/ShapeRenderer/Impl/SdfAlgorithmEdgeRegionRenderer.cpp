#include "SdfAlgorithmEdgeRegionRenderer.h"
#include "../../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmEdgeRegionRenderer::SdfAlgorithmEdgeRegionRenderer(GraphicsState::SharedPtr pGraphicsState)
    : SdfAlgorithmOutputRenderer(std::move(pGraphicsState))
{
}

SdfAlgorithmEdgeRegionRenderer::SharedPtr SdfAlgorithmEdgeRegionRenderer::create(
    GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new SdfAlgorithmEdgeRegionRenderer(std::move(pGraphicsState)));
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", offsetof(EdgeRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(EdgeRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmEdgeRegionRenderer::uploadShapeData()
{
    if (!mpShape->getAlgorithmOutput())
    {
        return;
    }

    std::vector<EdgeRegion> edgeRegions = mpShape->getAlgorithmOutput()->getEdgeRegions();

    auto center = mpShape->getCenter();
    double circleRadius = glm::max(mpShape->getCircumscribedCircleRadiusFromCenter() * 3, kMinCutDistanceFromOrigin);
    for (size_t i = 0; i < mPointsToCutAround; i++)
    {
        double t = (double(i) / double(mPointsToCutAround)) * glm::pi<double>() * 2;
        Vertex point{glm::cos(t), glm::sin(t)};
        auto cuttingRegions = {
            VertexRegion{point * circleRadius + center, 1, 5, 1e7},
            VertexRegion{point * circleRadius + center, -1, 5, 1e7},
        };
        EdgeRegion::cutWithVertices(edgeRegions, cuttingRegions);
    }

    std::vector<EdgeRegionBoundVertex> vertices;
    std::vector<uint32_t> indices;
    for (const auto &region : edgeRegions)
    {
        region.createMesh(vertices, indices, region.getEdge().getVertex1());
    }

    if (vertices.empty() || indices.empty())
    {
        mpRenderObject = nullptr;
    }
    else
    {
        mpRenderObject = RenderObject::create(vertices, indices, getVertexLayout());
    }
}
