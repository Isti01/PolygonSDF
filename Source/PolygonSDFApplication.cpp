#include "PolygonSDFApplication.h"
#include "Editor/Command/SetPolygonStackCommand.h"
#include "Rendering/PolygonRenderer/PolygonRendererFactory.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDFApplication::onGuiRender(Gui *pGui)
{
    mpGuiEditor->render(pGui);
}

void transformPolygonRenderer(PolygonRenderer::SharedPtr &pRenderer, float scale)
{
    auto translation = rmcv::translate(float3(.5, .5, 0));

    float mappedScale = glm::pow(1.8f, scale);
    auto scaling = rmcv::scale(float3{mappedScale, mappedScale, 1});
    pRenderer->transform(translation * scaling);
}

void PolygonSDFApplication::onLoad(RenderContext *pRenderContext)
{
    mpEditor = Editor::create(EditorStack::create());
    mpGuiEditor = GuiEditor::create(mpEditor);
    mpPolygonRenderer = PolygonRendererFactory::getPolygonRenderer();
    mpPolygonPresenter = PolygonPresenter::create(mpEditor);
    mpPolygonPresenter->setRenderer(mpPolygonRenderer);
    transformPolygonRenderer(mpPolygonRenderer, mScale);
    mpEditor->addCommand(SetPolygonStackCommand::create(Polygon::kExamplePolygon));
}

void PolygonSDFApplication::onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);

    mpPolygonPresenter->render(pRenderContext, pTargetFbo);
}

void PolygonSDFApplication::onShutdown()
{
}

bool PolygonSDFApplication::onKeyEvent(const KeyboardEvent &keyEvent)
{
    return false;
}

bool PolygonSDFApplication::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mouseEvent.type == Falcor::MouseEvent::Type::Wheel)
    {
        mScale += mouseEvent.wheelDelta.y * mScaleSpeed;
        transformPolygonRenderer(mpPolygonRenderer, mScale);
    }

    return false;
}

void PolygonSDFApplication::onHotReload(HotReloadFlags reloaded)
{
}

void PolygonSDFApplication::onResizeSwapChain(uint32_t width, uint32_t height)
{
}
