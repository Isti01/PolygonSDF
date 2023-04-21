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
