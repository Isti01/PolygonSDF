#include "PolygonOutlineRenderer.h"
#include "../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

void PolygonOutlineRenderer::init()
{
    Program::Desc desc;
    desc.addShaderLibrary("PolygonSDF/Shaders/SolidColor.slang").vsEntry("vsMain").psEntry("psMain");

    mpGraphicsState = GraphicsState::create();
    mpGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));
    mpGraphicsState->setProgram(GraphicsProgram::create(desc));
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
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

void PolygonOutlineRenderer::renderImpl(RenderContext *context) const
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpRenderObject);

    mpGraphicsState->setVao(mpRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpRenderObject->indexCount, 0, 0);
}

void PolygonOutlineRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
}
