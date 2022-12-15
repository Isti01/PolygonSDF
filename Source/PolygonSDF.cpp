#include "PolygonSDF.h"

using namespace Falcor;

namespace
{
const std::vector<psdf::PolygonSDF::FullScreenTriangleVertex> kFullScreenTriangleVertices{{
    {{-1, -1, 0}, {0, 0}},
    {{3, -1, 0}, {2, 0}},
    {{-1, 3, 0}, {0, 2}},
}};
const std::vector<uint32_t> kFullScreenTriangleIndexes{{0, 1, 2}};
} // namespace

void psdf::PolygonSDF::onGuiRender(Gui *pGui)
{
}

psdf::RenderObject::SharedPtr psdf::PolygonSDF::createTriangleObject() const
{
    const auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", 0, ResourceFormat::RGB32Float, 1, 0);
    pBufferLayout->addElement("TEX_COORDS", 12, ResourceFormat::RG32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);

    return RenderObject::create(kFullScreenTriangleVertices, kFullScreenTriangleIndexes, pLayout);
}

void psdf::PolygonSDF::onLoad(RenderContext *pRenderContext)
{
    object = createTriangleObject();

    Program::Desc desc;
    desc.addShaderLibrary("PolygonSDF/Shaders/PolygonSDF.slang").vsEntry("vsMain").psEntry("psMain");

    mpGraphicsState = GraphicsState::create();
    mpGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));
    mpGraphicsState->setProgram(GraphicsProgram::create(desc));
    mpGraphicsState->setVao(object->pVao);
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
}

void psdf::PolygonSDF::onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);
    mpGraphicsState->setFbo(pTargetFbo);
    pRenderContext->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), object->indexCount, 0, 0);
}

void psdf::PolygonSDF::onShutdown()
{
}

bool psdf::PolygonSDF::onKeyEvent(const KeyboardEvent &keyEvent)
{
    return false;
}

bool psdf::PolygonSDF::onMouseEvent(const MouseEvent &mouseEvent)
{
    return false;
}

void psdf::PolygonSDF::onHotReload(HotReloadFlags reloaded)
{
}

void psdf::PolygonSDF::onResizeSwapChain(uint32_t width, uint32_t height)
{
}
