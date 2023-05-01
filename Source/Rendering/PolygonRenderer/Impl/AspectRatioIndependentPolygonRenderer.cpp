#include "AspectRatioIndependentPolygonRenderer.h"

using namespace Falcor;
using namespace psdf;

AspectRatioIndependentPolygonRenderer::SharedPtr AspectRatioIndependentPolygonRenderer::create(
    PolygonRenderer::SharedPtr pPolygonRenderer)
{
    return SharedPtr(new AspectRatioIndependentPolygonRenderer(std::move(pPolygonRenderer)));
}

AspectRatioIndependentPolygonRenderer::AspectRatioIndependentPolygonRenderer(
    PolygonRenderer::SharedPtr pPolygonRenderer)
    : ProxyPolygonRenderer(std::move(pPolygonRenderer))
{
}

void AspectRatioIndependentPolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    updateAspectRatio();

    mAspectRatio =
        pFbo->getHeight() != 0 && pFbo->getWidth() != 0 ? ((float)pFbo->getWidth() / (float)pFbo->getHeight()) : 1;
    mpPolygonRenderer->setFbo(pFbo);
}

void AspectRatioIndependentPolygonRenderer::transformImpl()
{
    float4x4 correction;
    if (mAspectRatio > 1)
    {
        correction = rmcv::scale(float3{1 / mAspectRatio, 1, 1});
    }
    else
    {
        correction = rmcv::scale(float3{1, mAspectRatio, 1});
    }
    mpPolygonRenderer->transform(correction * mTransform);
}

void AspectRatioIndependentPolygonRenderer::updateAspectRatio()
{
    transform(mTransform);
}

void AspectRatioIndependentPolygonRenderer::setPropertyImpl(const PolygonRendererProperty &rendererProperty)
{
    mpPolygonRenderer->setProperty(rendererProperty);
}
