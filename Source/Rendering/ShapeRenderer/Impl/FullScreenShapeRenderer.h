#pragma once

#include "../../FullScreenTriangle.h"
#include "../ShapeRenderer.h"

namespace psdf
{
using namespace Falcor;

class FullScreenShapeRenderer : public ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<FullScreenShapeRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void transformImpl() override;

  protected:
    FullScreenShapeRenderer(GraphicsState::SharedPtr pGraphicsState);

    void init() override;
    void uploadShapeData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;

  private:
    bool mEnabled = true;
    GraphicsState::SharedPtr mpGraphicsState;
    GraphicsVars::SharedPtr mpGraphicsVars;
    FullScreenTriangle::SharedPtr mpFullscreenTriangle;
};

} // namespace psdf
