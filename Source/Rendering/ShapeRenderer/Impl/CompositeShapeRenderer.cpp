#include "CompositeShapeRenderer.h"

using namespace psdf;

CompositeShapeRenderer::CompositeShapeRenderer(std::vector<ShapeRenderer::SharedPtr> renderers)
    : mRenderers(std::move(renderers))
{
}

CompositeShapeRenderer::SharedPtr CompositeShapeRenderer::create(std::vector<ShapeRenderer::SharedPtr> renderers)
{
    return SharedPtr(new CompositeShapeRenderer(std::move(renderers)));
}

void CompositeShapeRenderer::init()
{
}

void CompositeShapeRenderer::uploadShapeData()
{
}

float4x4 CompositeShapeRenderer::getTransform() const
{
    return mTransform;
}

void CompositeShapeRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    for (const ShapeRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->setFbo(pFbo);
    }
}

void CompositeShapeRenderer::transformImpl()
{
    for (const ShapeRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->transform(mTransform);
    }
}
void CompositeShapeRenderer::renderImpl(Falcor::RenderContext *pRenderContext)
{
    for (const ShapeRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->render(pRenderContext);
    }
}
void CompositeShapeRenderer::setShape(const Shape::SharedPtr &pShape)
{
    mpShape = pShape;
    for (ShapeRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->setShape(pShape);
    }
}

void CompositeShapeRenderer::setPropertyImpl(const ShapeRendererProperty &rendererProperty)
{
    for (const ShapeRenderer::SharedPtr &pRenderer : mRenderers)
    {
        pRenderer->setProperty(rendererProperty);
    }
}
