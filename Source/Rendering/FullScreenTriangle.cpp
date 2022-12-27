#include "FullScreenTriangle.h"

#include <utility>

using namespace psdf;

struct FullScreenTriangleVertex
{
    float3 pos;
    float2 texCoords;
};

static const std::vector<FullScreenTriangleVertex> kFullScreenTriangleVertices{{
    {{-1, -1, 0}, {0, 0}},
    {{3, -1, 0}, {2, 0}},
    {{-1, 3, 0}, {0, 2}},
}};
static const std::vector<uint32_t> kFullScreenTriangleIndexes{{0, 1, 2}};

FullScreenTriangle::FullScreenTriangle(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

FullScreenTriangle::SharedPtr FullScreenTriangle::create(GraphicsState::SharedPtr pGraphicsState)
{
    return std::make_shared<FullScreenTriangle>(std::move(pGraphicsState));
}

RenderObject::SharedPtr createTriangleObject()
{
    const auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", 0, ResourceFormat::RGB32Float, 1, 0);
    pBufferLayout->addElement("TEX_COORDS", 12, ResourceFormat::RG32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);

    return RenderObject::create(kFullScreenTriangleVertices, kFullScreenTriangleIndexes, pLayout);
}

void FullScreenTriangle::init()
{
    mpTriangle = createTriangleObject();
    mpGraphicsState->setVao(mpTriangle->pVao);
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
}

void FullScreenTriangle::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
}
void FullScreenTriangle::render(RenderContext *pRenderContext)
{
    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpTriangle);

    pRenderContext->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpTriangle->indexCount, 0, 0);
}

GraphicsVars::SharedPtr FullScreenTriangle::getGraphicsVars()
{
    return mpProgramVars;
}
