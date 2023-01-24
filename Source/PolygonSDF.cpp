#include "PolygonSDF.h"
#include "Rendering/PolygonRenderer/AspectRatioIndependentPolygonRenderer.h"
#include "Rendering/PolygonRenderer/FullScreenPolygonRenderer.h"
#include "Rendering/PolygonRenderer/PolygonOutlineRenderer.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDF::onGuiRender(Gui *pGui)
{
    Gui::Window w(pGui, "PolygonSDF", {250, 200});
    w.text("Hello from PolygonSDF");
}

GraphicsState::SharedPtr getFullscreenRendererGS()
{
    auto pGraphicsState = GraphicsState::create();

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(false)));
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

    pGraphicsState->setDepthStencilState(DepthStencilState::create(DepthStencilState::Desc().setDepthEnabled(false)));
    auto pBlendState = BlendState::create(BlendState::Desc().setRtBlend(0, true).setRtParams(
        0, BlendState::BlendOp::Add, BlendState::BlendOp::Add, BlendState::BlendFunc::SrcAlpha,
        BlendState::BlendFunc::OneMinusSrcAlpha, BlendState::BlendFunc::One, BlendState::BlendFunc::One));
    pGraphicsState->setBlendState(pBlendState);
    pGraphicsState->setProgram(GraphicsProgram::create(Program::Desc()
                                                           .addShaderLibrary("PolygonSDF/Shaders/SolidColor.3d.slang")
                                                           .vsEntry("vsMain")
                                                           .psEntry("psMain")));

    return pGraphicsState;
}

PolygonRenderer::SharedPtr createPolygonRenderer()
{
    auto combinedRenderers = CompositePolygonRenderer::create(std::vector<PolygonRenderer::SharedPtr>{
        std::static_pointer_cast<PolygonRenderer>(FullScreenPolygonRenderer::create(getFullscreenRendererGS())),
        std::static_pointer_cast<PolygonRenderer>(
            PolygonOutlineRenderer::create(getOutlineRendererGS(), float4(1, 0, 0, 1))),
    });
    return std::static_pointer_cast<PolygonRenderer>(AspectRatioIndependentPolygonRenderer::create(combinedRenderers));
}

void transformPolygonRenderer(PolygonRenderer::SharedPtr &pRenderer, float scale)
{
    auto translation = rmcv::translate(float3(.5, .5, 0));

    float mappedScale = glm::pow(1.8, scale);
    auto scaling = rmcv::scale(float3{mappedScale, mappedScale, 1});
    pRenderer->transform(translation * scaling);
}

void PolygonSDF::onLoad(RenderContext *pRenderContext)
{
    mpPolygonRenderer = createPolygonRenderer();
    transformPolygonRenderer(mpPolygonRenderer, mScale);

    auto polygon = Polygon::create({{{.5, 0}}, {{0, .5}}, {{-.5, 0}}, {{0, -.5}}});
    mpPolygonRenderer->setPolygon(polygon);
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
        transformPolygonRenderer(mpPolygonRenderer, mScale);
    }

    return false;
}

void PolygonSDF::onHotReload(HotReloadFlags reloaded)
{
}

void PolygonSDF::onResizeSwapChain(uint32_t width, uint32_t height)
{
}
