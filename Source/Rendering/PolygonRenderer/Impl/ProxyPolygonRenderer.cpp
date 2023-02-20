#include "ProxyPolygonRenderer.h"

using namespace Falcor;
using namespace psdf;

ProxyPolygonRenderer::ProxyPolygonRenderer(PolygonRenderer::SharedPtr pPolygonRenderer)
    : mpPolygonRenderer(std::move(pPolygonRenderer))
{
}

float4x4 ProxyPolygonRenderer::getTransform() const
{
    return mpPolygonRenderer->getTransform();
}

void ProxyPolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    mpPolygonRenderer->setFbo(pFbo);
}

void ProxyPolygonRenderer::setPolygon(const Polygon::SharedPtr &pPolygon)
{
    mpPolygon = pPolygon;
    mpPolygonRenderer->setPolygon(pPolygon);
}

void ProxyPolygonRenderer::init()
{
}

void ProxyPolygonRenderer::uploadPolygonData()
{
}

void ProxyPolygonRenderer::renderImpl(RenderContext *pRenderContext)
{
    mpPolygonRenderer->render(pRenderContext);
}
void ProxyPolygonRenderer::transformImpl()
{
    mpPolygonRenderer->transform(mTransform);
}
