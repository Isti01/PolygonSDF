#pragma once

#include <Falcor.h>
#include <utility>

#include "./Rendering/RenderObject.h"
#include "Rendering/FullScreenTriangle.h"
#include "Rendering/PolygonRenderer/CompositePolygonRenderer.h"


namespace psdf
{
using namespace Falcor;

class PolygonSDF : public IRenderer
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
    PolygonRenderer::SharedPtr mpPolygonRenderer = nullptr;
};

} // namespace psdf
