#pragma once

#include "../FullScreenTriangle.h"
#include "PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class FullScreenPolygonRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<FullScreenPolygonRenderer>;

    FullScreenPolygonRenderer(GraphicsState::SharedPtr pGraphicsState);
    void setFbo(const Fbo::SharedPtr &pFbo) const override;
    void transformImpl() override;

  protected:
    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) const override;

  private:
    GraphicsState::SharedPtr mpGraphicsState;
    GraphicsVars::SharedPtr mpGraphicsVars;
    FullScreenTriangle::SharedPtr mpFullscreenTriangle;
};

} // namespace psdf
