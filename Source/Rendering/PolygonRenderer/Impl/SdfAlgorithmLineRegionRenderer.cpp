#include "SdfAlgorithmLineRegionRenderer.h"
#include "../../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmLineRegionRenderer::SdfAlgorithmLineRegionRenderer(GraphicsState::SharedPtr pGraphicsState)
    : SdfAlgorithmOutputRenderer(std::move(pGraphicsState))
{
}

SdfAlgorithmLineRegionRenderer::SharedPtr SdfAlgorithmLineRegionRenderer::create(
    GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new SdfAlgorithmLineRegionRenderer(std::move(pGraphicsState)));
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", offsetof(LineRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(LineRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmLineRegionRenderer::uploadPolygonData()
{
    if (!mpPolygon->getAlgorithmOutput())
    {
        return;
    }

    std::vector<LineRegion> lineRegions = mpPolygon->getAlgorithmOutput()->getLineRegions();

    double circleRadius = glm::max(getMaxDistanceFromOriginInPolygon(mpPolygon) * 3, kMinCutDistanceFromOrigin);
    auto center = mpPolygon->getCenter();
    for (size_t i = 0; i < mPointsToCutAround; i++)
    {
        double t = (double(i) / double(mPointsToCutAround)) * glm::pi<double>() * 2;
        Point point{glm::cos(t), glm::sin(t)};
        LineRegion::cutWithPoints(lineRegions, {PointRegion{point * circleRadius + center, 1}});
    }

    std::vector<LineRegionBoundVertex> vertices;
    std::vector<uint32_t> indices;
    for (const auto &region : lineRegions)
    {
        region.createMesh(vertices, indices, region.getSegment().getPoint1());
    }

    mpRenderObject = RenderObject::create(vertices, indices, getVertexLayout());
}
