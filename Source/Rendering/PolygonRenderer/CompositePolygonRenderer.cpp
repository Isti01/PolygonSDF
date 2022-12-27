#include "CompositePolygonRenderer.h"

using namespace psdf;

CompositePolygonRenderer::CompositePolygonRenderer(std::vector<PolygonRenderer::SharedPtr> renderers)
    : mRenderers(std::move(renderers))
{
}

void CompositePolygonRenderer::init()
{
}

void CompositePolygonRenderer::uploadPolygonData()
{
}

void CompositePolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo) const
{
    for (const PolygonRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->setFbo(pFbo);
    }
}

void CompositePolygonRenderer::renderImpl(Falcor::RenderContext *pRenderContext) const
{
    for (const PolygonRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->render(pRenderContext);
    }
}

void CompositePolygonRenderer::setPolygon(const Polygon::SharedPtr &pPolygon)
{
    mpPolygon = pPolygon;
    for (PolygonRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->setPolygon(pPolygon);
    }
}
