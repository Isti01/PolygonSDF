#include "SdfAlgorithmVertexRegionRenderer.h"
#include "../../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmVertexRegionRenderer::SdfAlgorithmVertexRegionRenderer(GraphicsState::SharedPtr pGraphicsState)
    : SdfAlgorithmOutputRenderer(std::move(pGraphicsState))
{
}

SdfAlgorithmVertexRegionRenderer::SharedPtr SdfAlgorithmVertexRegionRenderer::create(
    GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new SdfAlgorithmVertexRegionRenderer(std::move(pGraphicsState)));
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("RV", offsetof(VertexRegionBoundVertex, vertex), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("POS", offsetof(VertexRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 1);
    pBufferLayout->addElement("DST", offsetof(VertexRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 2);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmVertexRegionRenderer::uploadShapeData()
{
    if (!mpShape->getAlgorithmOutput())
    {
        return;
    }

    std::vector<VertexRegion> vertexRegions = mpShape->getAlgorithmOutput()->getVertexRegions();
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
        VertexRegion::cutWithVertices(vertexRegions, cuttingRegions);
    }

    std::vector<VertexRegionBoundVertex> vertices;
    std::vector<uint32_t> indices;
    for (const auto &region : vertexRegions)
    {
        region.createMesh(vertices, indices, region.getVertex());
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
