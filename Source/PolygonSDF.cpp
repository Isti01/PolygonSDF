#include "PolygonSDF.h"
#include "Rendering/PolygonRenderer/PolygonOutlineRenderer.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDF::onGuiRender(Gui *pGui)
{
}

void PolygonSDF::onLoad(RenderContext *pRenderContext)
{
    Program::Desc programDesc;
    programDesc.addShaderLibrary("PolygonSDF/Shaders/SolidColor.3d.slang").vsEntry("vsMain").psEntry("psMain");

    auto pGraphicsState = GraphicsState::create();
    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));
    BlendState::Desc blendDesc;

    pGraphicsState->setBlendState(BlendState::create(blendDesc));
    pGraphicsState->setProgram(GraphicsProgram::create(programDesc));

    std::vector<PolygonRenderer::SharedPtr> renderers = {
        std::shared_ptr<PolygonRenderer>(new PolygonOutlineRenderer(pGraphicsState, float4(1, 0, 0, .5))),
    };
    mpPolygonRenderer = std::make_shared<CompositePolygonRenderer>(renderers);
    mpPolygonRenderer->setPolygon(Polygon::create({{{.5, 0}}, {{0, .5}}, {{-.5, 0}}, {{0, -.5}}}));

    mpFullScreenTriangle = FullScreenTriangle::create(
        Program::Desc().addShaderLibrary("PolygonSDF/Shaders/UVColor.3d.slang").vsEntry("vsMain").psEntry("psMain"));
    mpFullScreenTriangle->init();
}

void PolygonSDF::onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);

    if (mShowPolygon)
    {
        mpPolygonRenderer->setFbo(pTargetFbo);
        mpPolygonRenderer->render(pRenderContext);
    }
    else
    {
        mpFullScreenTriangle->setFbo(pTargetFbo);
        mpFullScreenTriangle->render(pRenderContext);
    }
}

void PolygonSDF::onShutdown()
{
}

bool PolygonSDF::onKeyEvent(const KeyboardEvent &keyEvent)
{
    if (keyEvent.type != Falcor::KeyboardEvent::Type::KeyPressed)
    {
        return false;
    }

    if (keyEvent.key == Falcor::Input::Key::Space)
    {
        mShowPolygon = !mShowPolygon;
        return true;
    }

    return false;
}

bool PolygonSDF::onMouseEvent(const MouseEvent &mouseEvent)
{
    return false;
}

void PolygonSDF::onHotReload(HotReloadFlags reloaded)
{
}

void PolygonSDF::onResizeSwapChain(uint32_t width, uint32_t height)
{
}
