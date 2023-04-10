#pragma once

#include <Falcor.h>
#include <utility>

#include "Editor/Consumer/GuiStateEditorConsumer.h"
#include "Editor/Core/Editor.h"
#include "Editor/Event/Menu/EventMenu.h"
#include "Editor/GuiEditor/GuiEditor.h"
#include "Editor/VisualEditor/VisualEditor.h"

namespace psdf
{
using namespace Falcor;

class PolygonSDFApplication : public IRenderer
{
  public:
    void onLoad(RenderContext *pRenderContext) override;
    void onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) override;
    void onShutdown() override;
    void onResizeSwapChain(uint32_t width, uint32_t height) override;
    bool onKeyEvent(const KeyboardEvent &keyEvent) override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void onHotReload(HotReloadFlags reloaded) override;
    void onGuiRender(Gui *pGui) override;

  private:
    Editor::SharedPtr mpEditor = nullptr;
    GuiEditor::SharedPtr mpGuiEditor = nullptr;
    VisualEditor::SharedPtr mpVisualEditor = nullptr;
    EventMenu::SharedPtr mpEventMenu = nullptr;
    GuiStateEditorConsumer::SharedPtr mpGuiStateConsumer = nullptr;
};

} // namespace psdf
