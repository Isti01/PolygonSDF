#include "PolygonSDF.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDF::onGuiRender(Gui *pGui)
{
}

void PolygonSDF::onLoad(RenderContext *pRenderContext)
{
    mpPolygonRenderer = std::make_shared<PolygonOutlineRenderer>();
    mpPolygonRenderer->setPolygon(Polygon::create({{{.5, 0}}, {{0, .5}}, {{-.5, 0}}, {{0, -.5}}}));

    mpFullScreenTriangle = FullScreenTriangle::create(
        Program::Desc().addShaderLibrary("PolygonSDF/Shaders/UVColor.slang").vsEntry("vsMain").psEntry("psMain"));
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
