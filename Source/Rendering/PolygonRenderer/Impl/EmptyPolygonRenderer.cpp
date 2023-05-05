#include "EmptyPolygonRenderer.h"

using namespace psdf;
using namespace Falcor;

EmptyPolygonRenderer::SharedPtr EmptyPolygonRenderer::create()
{
    return SharedPtr(new EmptyPolygonRenderer());
}

void EmptyPolygonRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
}

float4x4 EmptyPolygonRenderer::getTransform() const
{
    return rmcv::identity<float4x4>();
}

void EmptyPolygonRenderer::init()
{
}

void EmptyPolygonRenderer::uploadPolygonData()
{
}

void EmptyPolygonRenderer::renderImpl(RenderContext *pRenderContext)
{
}

void EmptyPolygonRenderer::transformImpl()
{
}

void EmptyPolygonRenderer::setPropertyImpl(const PolygonRendererProperty &rendererProperty)
{
}
