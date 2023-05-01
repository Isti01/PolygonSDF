#pragma once

#include "../../FullScreenTriangle.h"
#include "../PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class FullScreenPolygonRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<FullScreenPolygonRenderer>;

    static constexpr const char *kFullScreenPolygonRendererEnabledProperty = "FullScreenPolygonRendererEnabledProperty";
    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void setProperty(const PolygonRendererProperty &rendererProperty) override;
    void transformImpl() override;

  protected:
    FullScreenPolygonRenderer(GraphicsState::SharedPtr pGraphicsState);

    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) override;

  private:
    bool mEnabled = true;
    GraphicsState::SharedPtr mpGraphicsState;
    GraphicsVars::SharedPtr mpGraphicsVars;
    FullScreenTriangle::SharedPtr mpFullscreenTriangle;
};

} // namespace psdf
