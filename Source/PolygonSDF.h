#pragma once

#include <Falcor.h>
#include <utility>

#include "./Rendering/RenderObject.h"


namespace psdf
{
using namespace Falcor;

class PolygonSDF : public IRenderer
{
  public:
    struct FullScreenTriangleVertex
    {
        float3 pos;
        float2 texCoords;
    };

  public:
    void onLoad(RenderContext *pRenderContext) override;
    [[nodiscard]] RenderObject::SharedPtr createTriangleObject() const;
    void onFrameRender(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) override;
    void onShutdown() override;
    void onResizeSwapChain(uint32_t width, uint32_t height) override;
    bool onKeyEvent(const KeyboardEvent &keyEvent) override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void onHotReload(HotReloadFlags reloaded) override;
    void onGuiRender(Gui *pGui) override;

  private:
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    GraphicsState::SharedPtr mpGraphicsState = nullptr;

    RenderObject::SharedPtr object = nullptr;
};

} // namespace psdf
