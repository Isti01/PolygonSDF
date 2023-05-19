#include "ShapeOutlineRenderer.h"
#include "../../../Util/RangeGenerator.h"
#include "../RendererProperties.h"

using namespace Falcor;
using namespace psdf;

ShapeOutlineRenderer::ShapeOutlineRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

ShapeOutlineRenderer::SharedPtr ShapeOutlineRenderer::create(GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new ShapeOutlineRenderer(std::move(pGraphicsState)));
}

void ShapeOutlineRenderer::init()
{
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
}

float4x4 ShapeOutlineRenderer::getTransform() const
{
    return mTransform;
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", 0, ResourceFormat::RG32Float, 1, 0);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void ShapeOutlineRenderer::uploadShapeData()
{
    auto edges = mpShape->getAllFloatEdges();

    std::vector<uint32_t> indices(edges.size() * 2);
    std::generate(indices.begin(), indices.end(), RangeGenerator());

    mpRenderObject = RenderObject::create(edges, indices, getVertexLayout(), Vao::Topology::LineList);
}

void ShapeOutlineRenderer::renderImpl(RenderContext *context)
{
    if (!mEnabled)
    {
        return;
    }
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpRenderObject);

    mpGraphicsState->setVao(mpRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpRenderObject->indexCount, 0, 0);
}

void ShapeOutlineRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    mpProgramVars["Data"]["iTransform"] = mTransform;
}

void ShapeOutlineRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
}

void ShapeOutlineRenderer::setPropertyImpl(const ShapeRendererProperty &rendererProperty)
{
    if (rendererProperty.key == RendererProperties::kPolygonOutlineRendererEnabledProperty)
    {
        if (auto *enabled = std::get_if<bool>(&rendererProperty.value))
        {
            mEnabled = *enabled;
        }
    }
    else if (rendererProperty.key == RendererProperties::kPolygonOutlineColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpProgramVars["Data"]["iColor"] = float4(*color, 1);
        }
    }
}
