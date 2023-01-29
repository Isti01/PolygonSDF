#include "FullScreenPolygonRenderer.h"

using namespace Falcor;
using namespace psdf;

FullScreenPolygonRenderer::FullScreenPolygonRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

FullScreenPolygonRenderer::SharedPtr FullScreenPolygonRenderer::create(GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new FullScreenPolygonRenderer(std::move(pGraphicsState)));
}

void FullScreenPolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    mpFullscreenTriangle->setFbo(pFbo);
}

void FullScreenPolygonRenderer::init()
{
    mpFullscreenTriangle = FullScreenTriangle::create(mpGraphicsState);
    mpFullscreenTriangle->init();
    mpGraphicsVars = mpFullscreenTriangle->getGraphicsVars();
}

void FullScreenPolygonRenderer::uploadPolygonData()
{
    auto pPointBuffer = Buffer::createStructured(mpGraphicsVars["points"], mpPolygon->getPoints().size(),
                                                 Resource::BindFlags::ShaderResource, Buffer::CpuAccess::None,
                                                 mpPolygon->getPoints().data(), false);

    mpGraphicsVars->setBuffer("points", pPointBuffer);
}

void FullScreenPolygonRenderer::renderImpl(RenderContext *pRenderContext)
{
    mpFullscreenTriangle->render(pRenderContext);
}

void FullScreenPolygonRenderer::transformImpl()
{
    // we need the inverse, because we are transforming the origin instead of the objects
    mpGraphicsVars["Data"]["iTransform"] = rmcv::inverse(mTransform);
}
