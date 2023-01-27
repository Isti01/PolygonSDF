#include "PolygonOutlineRenderer.h"
#include "../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

PolygonOutlineRenderer::PolygonOutlineRenderer(GraphicsState::SharedPtr pGraphicsState, const float4 &color)
    : mpGraphicsState(std::move(pGraphicsState)), mColor(color)
{
}

PolygonOutlineRenderer::SharedPtr PolygonOutlineRenderer::create(GraphicsState::SharedPtr pGraphicsState,
                                                                 const float4 &color)
{
    return SharedPtr(new PolygonOutlineRenderer(std::move(pGraphicsState), color));
}

void PolygonOutlineRenderer::init()
{
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
    uploadColor();
}

float4 PolygonOutlineRenderer::getColor() const
{
    return mColor;
}

void PolygonOutlineRenderer::setColor(const float4 &color)
{
    this->mColor = color;
    uploadColor();
}

VertexLayout::SharedPtr getVertexLayout()
{
    const auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", 0, ResourceFormat::RG32Float, 1, 0);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void PolygonOutlineRenderer::uploadPolygonData()
{
    auto segments = mpPolygon->getSegments();

    std::vector<uint32_t> indices(segments->size() * 2);
    std::generate(indices.begin(), indices.end(), RangeGenerator());

    mpRenderObject = RenderObject::create(*segments, indices, getVertexLayout(), Vao::Topology::LineList);
}

void PolygonOutlineRenderer::renderImpl(RenderContext *context)
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpRenderObject);

    mpGraphicsState->setVao(mpRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpRenderObject->indexCount, 0, 0);
}

void PolygonOutlineRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    const float4x4 baseTransform = rmcv::translate(float3{-1, -1, 0}) * rmcv::scale(float3{2, 2, 1});
    const auto transform = baseTransform * mTransform;
    mpProgramVars["Data"]["iTransform"] = transform;
}

void PolygonOutlineRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
}

void PolygonOutlineRenderer::uploadColor()
{
    if (mpProgramVars)
    {
        mpProgramVars["Data"]["iColor"] = mColor;
    }
}
