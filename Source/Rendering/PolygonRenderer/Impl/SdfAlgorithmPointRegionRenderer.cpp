#include "SdfAlgorithmPointRegionRenderer.h"
#include "../../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmPointRegionRenderer::SdfAlgorithmPointRegionRenderer(GraphicsState::SharedPtr pGraphicsState)
    : SdfAlgorithmOutputRenderer(std::move(pGraphicsState))
{
}

SdfAlgorithmPointRegionRenderer::SharedPtr SdfAlgorithmPointRegionRenderer::create(
    GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new SdfAlgorithmPointRegionRenderer(std::move(pGraphicsState)));
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("RV", offsetof(PointRegionBoundVertex, point), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("POS", offsetof(PointRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 1);
    pBufferLayout->addElement("DST", offsetof(PointRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 2);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmPointRegionRenderer::uploadPolygonData()
{
    if (!mpPolygon->getAlgorithmOutput())
    {
        return;
    }

    std::vector<PointRegion> pointRegions = mpPolygon->getAlgorithmOutput()->getPointRegions();
    auto center = mpPolygon->getCenter();
    double circleRadius = glm::max(getMaxDistanceFromPointInPolygon(center, mpPolygon) * 3, kMinCutDistanceFromOrigin);
    for (size_t i = 0; i < mPointsToCutAround; i++)
    {
        double t = (double(i) / double(mPointsToCutAround)) * glm::pi<double>() * 2;
        Point point{glm::cos(t), glm::sin(t)};
        auto cuttingRegions = {
            PointRegion{point * circleRadius + center, 1},
            PointRegion{point * circleRadius + center, -1},
        };
        PointRegion::cutWithPoints(pointRegions, cuttingRegions);
    }

    std::vector<PointRegionBoundVertex> vertices;
    std::vector<uint32_t> indices;
    for (const auto &region : pointRegions)
    {
        region.createMesh(vertices, indices, region.getPoint());
    }

    mpRenderObject = RenderObject::create(vertices, indices, getVertexLayout());
}
