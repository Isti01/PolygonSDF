#include "FullScreenPolygonRenderer.h"

using namespace Falcor;
using namespace psdf;

FullScreenPolygonRenderer::FullScreenPolygonRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

void FullScreenPolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo) const
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
    auto pPointBuffer = Buffer::createStructured(mpGraphicsVars["points"], mpPolygon->getPoints()->size(),
                                                 Resource::BindFlags::ShaderResource, Buffer::CpuAccess::None,
                                                 mpPolygon->getPoints()->data(), false);

    mpGraphicsVars->setBuffer("points", pPointBuffer);
}

void FullScreenPolygonRenderer::renderImpl(RenderContext *pRenderContext) const
{
    mpFullscreenTriangle->render(pRenderContext);
}

void FullScreenPolygonRenderer::transformImpl()
{
    mpGraphicsVars["Data"]["iTransform"] = rmcv::inverse(mTransform);
}
