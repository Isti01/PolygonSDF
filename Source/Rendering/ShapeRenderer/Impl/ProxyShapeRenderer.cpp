#include "ProxyShapeRenderer.h"

using namespace Falcor;
using namespace psdf;

ProxyShapeRenderer::ProxyShapeRenderer(ShapeRenderer::SharedPtr pPolygonRenderer)
    : mpRenderer(std::move(pPolygonRenderer))
{
}

float4x4 ProxyShapeRenderer::getTransform() const
{
    return mpRenderer->getTransform();
}

void ProxyShapeRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    mpRenderer->setFbo(pFbo);
}

void ProxyShapeRenderer::setShape(const Shape::SharedPtr &pShape)
{
    mpShape = pShape;
    mpRenderer->setShape(pShape);
}

void ProxyShapeRenderer::init()
{
}

void ProxyShapeRenderer::uploadShapeData()
{
}

void ProxyShapeRenderer::renderImpl(RenderContext *pRenderContext)
{
    mpRenderer->render(pRenderContext);
}
void ProxyShapeRenderer::transformImpl()
{
    mpRenderer->transform(mTransform);
}
