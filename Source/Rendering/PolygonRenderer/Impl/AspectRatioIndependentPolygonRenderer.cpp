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
    float camWidth = kOrthoCamWidth;
    float camHeight = kOrthoCamWidth / mAspectRatio;
    float4x4 projection = rmcv::ortho(camWidth, -camWidth, -camHeight, camHeight, -250.0f, 250.0f);
    float4x4 view = rmcv::lookAt(float3(0, 0, -1), float3(0, 0, 0), float3(0, 1, 0));
    auto vp = projection * view;
    mpPolygonRenderer->transform(vp * mTransform);
}

void AspectRatioIndependentPolygonRenderer::updateAspectRatio()
{
    transform(mTransform);
}

void AspectRatioIndependentPolygonRenderer::setPropertyImpl(const PolygonRendererProperty &rendererProperty)
{
    mpPolygonRenderer->setProperty(rendererProperty);
}
