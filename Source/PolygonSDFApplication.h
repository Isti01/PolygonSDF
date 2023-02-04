#pragma once

#include <Falcor.h>
#include <utility>

#include "./Rendering/RenderObject.h"
#include "Editor/Core/Editor.h"
#include "Editor/Core/EditorConsumer.h"
#include "Editor/GuiEditor/GuiEditor.h"
#include "Editor/PolygonPresenter/PolygonPresenter.h"
#include "Rendering/FullScreenTriangle.h"
#include "Rendering/PolygonRenderer/Impl/CompositePolygonRenderer.h"

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
    float mScale = .5f;
    float mScaleSpeed = 0.1f;

    PolygonPresenter::SharedPtr mpPolygonPresenter = nullptr;
    PolygonRenderer::SharedPtr mpPolygonRenderer = nullptr;
    Editor::SharedPtr mpEditor = nullptr;
    GuiEditor::SharedPtr mpGuiEditor = nullptr;
};

} // namespace psdf
