#include "CompositePolygonRenderer.h"

using namespace psdf;

CompositePolygonRenderer::CompositePolygonRenderer(std::vector<PolygonRenderer::SharedPtr> renderers)
    : mRenderers(std::move(renderers))
{
}

CompositePolygonRenderer::SharedPtr CompositePolygonRenderer::create(std::vector<PolygonRenderer::SharedPtr> renderers)
{
    return SharedPtr(new CompositePolygonRenderer(std::move(renderers)));
}

void CompositePolygonRenderer::init()
{
}

void CompositePolygonRenderer::uploadPolygonData()
{
}

float4x4 CompositePolygonRenderer::getTransform() const
{
    return mTransform;
}

void CompositePolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    for (const PolygonRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->setFbo(pFbo);
    }
}

void CompositePolygonRenderer::transformImpl()
{
    for (const PolygonRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->transform(mTransform);
    }
}
void CompositePolygonRenderer::renderImpl(Falcor::RenderContext *pRenderContext)
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
