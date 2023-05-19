#pragma once

#include <Falcor.h>
#include <utility>

#include "../Source/Editor/Consumer/GuiStateEditorConsumer.h"
#include "../Source/Editor/Core/Editor.h"
#include "../Source/Editor/GuiEditor/GuiEditor.h"
#include "../Source/Editor/VisualEditor/VisualEditor.h"

namespace psdf
{
using namespace Falcor;

class PolygonSDFApplication : public IRenderer
{
  public:
    void onLoad(RenderContext *pRenderContext) override;
    void onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) override;
    void onShutdown() override;
    bool onKeyEvent(const KeyboardEvent &keyEvent) override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void onGuiRender(Gui *pGui) override;

  private:
    Editor::SharedPtr mpEditor = nullptr;
    GuiEditor::SharedPtr mpGuiEditor = nullptr;
    VisualEditor::SharedPtr mpVisualEditor = nullptr;
    GuiStateEditorConsumer::SharedPtr mpGuiStateConsumer = nullptr;
};

} // namespace psdf
