#include <numeric>

#include "SdfAlgorithmOutputRenderer.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmOutputRenderer::SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
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
    pBufferLayout->addElement("POS", offsetof(LineRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(LineRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

double SdfAlgorithmOutputRenderer::getMaxDistanceFromOriginInPolygon(const Polygon::SharedPtr &pPolygon)
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

void SdfAlgorithmOutputRenderer::setPolygon(const Polygon::SharedPtr &pPolygon)
{
    if (pPolygon)
    {
        Point average{0};
        const auto &polygons = pPolygon->getPolygons();
        double pointWeight = std::accumulate(polygons.cbegin(), polygons.cend(), 0.0,
                                             [](double count, const auto &p) { return count + p.getPoints().size(); });
        for (const auto &group : polygons)
        {
            for (const auto &point : group.getPoints())
            {
                average += point / pointWeight;
            }
        }
        mPolygonCenter = average;
    }
    PolygonRenderer::setPolygon(pPolygon);
}

void SdfAlgorithmOutputRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    const auto transform = mTransform * rmcv::translate(-float3{mPolygonCenter, 0});

    auto projection = rmcv::identity<float4x4>();
    if (mFboWidth != 0)
    {
        float width = float(mFboWidth);
        float orthoCamScaler = kOrthoCamSize / width;
        projection = rmcv::ortho(-orthoCamScaler * width, orthoCamScaler * width, -orthoCamScaler * width,
                                 orthoCamScaler * width, -250.0f, 250.0f);
    }
    auto view = rmcv::lookAt(float3(0, 0, -1), float3(0, 0, 0), float3(0, 1, 0));
    mpProgramVars["Data"]["iTransform"] = projection * view * transform;
}

void SdfAlgorithmOutputRenderer::renderImpl(RenderContext *context)
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpRenderObject);

    mpGraphicsState->setVao(mpRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpRenderObject->indexCount, 0, 0);
}

void SdfAlgorithmOutputRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
    mFboWidth = pFbo->getWidth();
    mFboHeight = pFbo->getHeight();
    transformImpl();
}
