#include "PolygonSDFApplication.h"
#include "Editor/Command/SetPolygonStackCommand.h"

#include <memory>

using namespace Falcor;
using namespace psdf;

void PolygonSDFApplication::onLoad(RenderContext *pRenderContext)
{
    mpEditor = Editor::create(EditorStack::create());
    mpGuiEditor = GuiEditor::create(mpEditor);
    mpVisualEditor = VisualEditor::create(mpEditor);
    mpEditor->addCommand(SetPolygonStackCommand::create(Polygon::kExamplePolygon));
    mpEventMenu = EventMenu::create(mpEditor);
}

void PolygonSDFApplication::onGuiRender(Gui *pGui)
{
    mpGuiEditor->render(pGui);
    mpEventMenu->renderGui(pGui);
}

void PolygonSDFApplication::onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo)
{
    constexpr float4 clearColor(0, 0, 0, 1);
    pRenderContext->clearFbo(pTargetFbo.get(), clearColor, 1.0f, 0, FboAttachmentType::All);

    mpVisualEditor->render(pRenderContext, pTargetFbo);
}

bool PolygonSDFApplication::onKeyEvent(const KeyboardEvent &keyEvent)
{
    return mpVisualEditor->onKeyEvent(keyEvent);
}

bool PolygonSDFApplication::onMouseEvent(const MouseEvent &mouseEvent)
{
    return mpVisualEditor->onMouseEvent(mouseEvent);
}

void PolygonSDFApplication::onHotReload(HotReloadFlags reloaded)
{
}

void PolygonSDFApplication::onResizeSwapChain(uint32_t width, uint32_t height)
{
}

void PolygonSDFApplication::onShutdown()
{
}
