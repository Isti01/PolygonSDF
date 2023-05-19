#include "AspectRatioIndependentShapeRenderer.h"

using namespace Falcor;
using namespace psdf;

AspectRatioIndependentShapeRenderer::SharedPtr AspectRatioIndependentShapeRenderer::create(
    ShapeRenderer::SharedPtr pShapeRenderer)
{
    return SharedPtr(new AspectRatioIndependentShapeRenderer(std::move(pShapeRenderer)));
}

AspectRatioIndependentShapeRenderer::AspectRatioIndependentShapeRenderer(ShapeRenderer::SharedPtr pShapeRenderer)
    : ProxyShapeRenderer(std::move(pShapeRenderer))
{
}

void AspectRatioIndependentShapeRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    float newAspectRatio =
        pFbo->getHeight() != 0 && pFbo->getWidth() != 0 ? ((float)pFbo->getWidth() / (float)pFbo->getHeight()) : 1;
    if (mAspectRatio != newAspectRatio)
    {
        mAspectRatio = newAspectRatio;
        updateAspectRatio();
    }

    mpRenderer->setFbo(pFbo);
}

void AspectRatioIndependentShapeRenderer::transformImpl()
{
    float camWidth = kOrthoCamWidth;
    float camHeight = kOrthoCamWidth / mAspectRatio;
    float4x4 projection = rmcv::ortho(camWidth, -camWidth, -camHeight, camHeight, -250.0f, 250.0f);
    float4x4 view = rmcv::lookAt(float3(0, 0, -1), float3(0, 0, 0), float3(0, 1, 0));
    auto vp = projection * view;
    mpRenderer->transform(vp * mTransform);
}

void AspectRatioIndependentShapeRenderer::updateAspectRatio()
{
    transform(mTransform);
}

void AspectRatioIndependentShapeRenderer::setPropertyImpl(const ShapeRendererProperty &rendererProperty)
{
    mpRenderer->setProperty(rendererProperty);
}
