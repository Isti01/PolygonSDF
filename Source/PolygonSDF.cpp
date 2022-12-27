#include "PolygonSDF.h"
#include "Rendering/PolygonRenderer/FullScreenPolygonRenderer.h"
#include "Rendering/PolygonRenderer/PolygonOutlineRenderer.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDF::onGuiRender(Gui *pGui)
{
}

GraphicsState::SharedPtr getFullscreenRendererGS()
{
    auto pGraphicsState = GraphicsState::create();

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));
    pGraphicsState->setProgram(
        GraphicsProgram::create(Program::Desc()
                                    .addShaderLibrary("PolygonSDF/Shaders/NaivePolygonDistance.3d.slang")
                                    .vsEntry("vsMain")
                                    .psEntry("psMain")));

    return pGraphicsState;
}

GraphicsState::SharedPtr getOutlineRendererGS()
{
    auto pGraphicsState = GraphicsState::create();

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(true)));
    pGraphicsState->setProgram(GraphicsProgram::create(Program::Desc()
                                                           .addShaderLibrary("PolygonSDF/Shaders/SolidColor.3d.slang")
                                                           .vsEntry("vsMain")
                                                           .psEntry("psMain")));

    return pGraphicsState;
}

void PolygonSDF::onLoad(RenderContext *pRenderContext)
{
    std::vector<PolygonRenderer::SharedPtr> renderers = {
        std::shared_ptr<PolygonRenderer>(new PolygonOutlineRenderer(getOutlineRendererGS(), float4(1, 0, 0, .5))),
        std::shared_ptr<PolygonRenderer>(new FullScreenPolygonRenderer(getFullscreenRendererGS())),
    };
    mpPolygonRenderer = std::make_shared<CompositePolygonRenderer>(renderers);
    mpPolygonRenderer->transform(rmcv::scale(float3{mScale, mScale, 1}) * rmcv::translate(float3{1, 1, 0}));
    mpPolygonRenderer->setPolygon(Polygon::create({{{.5, 0}}, {{0, .5}}, {{-.5, 0}}, {{0, -.5}}}));
}

void PolygonSDF::onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);

    mpPolygonRenderer->setFbo(pTargetFbo);
    mpPolygonRenderer->render(pRenderContext);
}

void PolygonSDF::onShutdown()
{
}

bool PolygonSDF::onKeyEvent(const KeyboardEvent &keyEvent)
{
    return false;
}

bool PolygonSDF::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mouseEvent.type == Falcor::MouseEvent::Type::Wheel)
    {
        mScale += mouseEvent.wheelDelta.y * mScaleSpeed;
        mpPolygonRenderer->transform(rmcv ::scale(float3{mScale, mScale, 1}) * rmcv::translate(float3{1, 1, 0}));
    }

    return false;
}

void PolygonSDF::onHotReload(HotReloadFlags reloaded)
{
}

void PolygonSDF::onResizeSwapChain(uint32_t width, uint32_t height)
{
}
