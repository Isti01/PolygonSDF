#include "SdfAlgorithmOutputRenderer.h"
#include "../../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmOutputRenderer::SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

SdfAlgorithmOutputRenderer::SharedPtr SdfAlgorithmOutputRenderer::create(GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new SdfAlgorithmOutputRenderer(std::move(pGraphicsState)));
}

void SdfAlgorithmOutputRenderer::init()
{
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
}

float4x4 SdfAlgorithmOutputRenderer::getTransform() const
{
    return mTransform;
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", offsetof(RegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(RegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

static double getMaxDistanceFromOriginInPolygon(const Polygon::SharedPtr &pPolygon)
{
    double maxDistance = glm::distance({0.0, 0.0}, pPolygon->getPolygons()[0].getPoints()[0]);
    for (const auto &subPolygon : pPolygon->getPolygons())
    {
        for (const auto &point : subPolygon.getPoints())
        {
            maxDistance = glm::max(maxDistance, glm::distance({0.0, 0.0}, point));
        }
    }
    return maxDistance;
}

void SdfAlgorithmOutputRenderer::uploadPolygonData()
{
    if (!mpPolygon->getAlgorithmOutput())
    {
        return;
    }

    std::vector<PointRegion> pointRegions = mpPolygon->getAlgorithmOutput()->getPointRegions();
    std::vector<LineRegion> lineRegions = mpPolygon->getAlgorithmOutput()->getLineRegions();

    double circleRadius = glm::max(getMaxDistanceFromOriginInPolygon(mpPolygon) * 3, kMinCutDistanceFromOrigin);

    for (size_t i = 0; i < kPointsToCutAround; i++)
    {
        double t = (double(i) / double(kPointsToCutAround)) * glm::pi<double>() * 2;
        Point point{glm::cos(t), glm::sin(t)};
        PointRegion::cutWithPoints(pointRegions, {PointRegion{point * circleRadius, 1}});
        LineRegion::cutWithPoints(lineRegions, {PointRegion{point * circleRadius, 1}});
    }

    std::vector<RegionBoundVertex> vertices;
    std::vector<uint32_t> indices;
    for (const auto &region : pointRegions)
    {
        region.createMesh(vertices, indices, region.getPoint());
    }

    mpPointRegionRenderObject = RenderObject::create(vertices, indices, getVertexLayout());

    vertices.clear();
    indices.clear();
    for (const auto &region : lineRegions)
    {
        region.createMesh(vertices, indices, region.getSegment().getPoint1());
    }

    mpLineRegionRenderObject = RenderObject::create(vertices, indices, getVertexLayout());
}

void SdfAlgorithmOutputRenderer::renderImpl(RenderContext *context)
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpPointRegionRenderObject);
    FALCOR_ASSERT(mpLineRegionRenderObject);

    mpGraphicsState->setVao(mpPointRegionRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpPointRegionRenderObject->indexCount, 0, 0);

    mpGraphicsState->setVao(mpLineRegionRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpLineRegionRenderObject->indexCount, 0, 0);
}

void SdfAlgorithmOutputRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    const auto transform = mTransform;

    auto projection = rmcv::identity<float4x4>();
    if (mFboWidth != 0)
    {
        projection = rmcv::perspective(glm::pi<float>() / 2, float(mFboWidth) / float(mFboHeight), 0.1f, 250.0f);
    }
    auto view = rmcv::lookAt(float3(0, 0, -10), float3(0, 0, 0), float3(0, 1, 0));
    mpProgramVars["Data"]["iTransform"] = projection * view * transform;
}

void SdfAlgorithmOutputRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
    mFboWidth = pFbo->getWidth();
    mFboHeight = pFbo->getHeight();
    transformImpl();
}
