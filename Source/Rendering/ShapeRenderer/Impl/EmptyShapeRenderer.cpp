#include "EmptyShapeRenderer.h"

using namespace psdf;
using namespace Falcor;

EmptyShapeRenderer::SharedPtr EmptyShapeRenderer::create()
{
    return SharedPtr(new EmptyShapeRenderer());
}

void EmptyShapeRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
}

float4x4 EmptyShapeRenderer::getTransform() const
{
    return rmcv::identity<float4x4>();
}

void EmptyShapeRenderer::init()
{
}

void EmptyShapeRenderer::uploadShapeData()
{
}

void EmptyShapeRenderer::renderImpl(RenderContext *pRenderContext)
{
}

void EmptyShapeRenderer::transformImpl()
{
}

void EmptyShapeRenderer::setPropertyImpl(const ShapeRendererProperty &rendererProperty)
{
}
