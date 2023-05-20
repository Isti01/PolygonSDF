#pragma once

#include "../../../Shape/Shape.h"
#include "../../RenderObject.h"
#include "../ShapeRenderer.h"

namespace psdf
{
using namespace Falcor;

class ShapeOutlineRenderer : public ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<ShapeOutlineRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;

  protected:
    ShapeOutlineRenderer(GraphicsState::SharedPtr pGraphicsState);

    void transformImpl() override;
    void init() override;
    void uploadShapeData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;

  private:
    bool mEnabled = true;
    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    RenderObject::SharedPtr mpRenderObject = nullptr;
};

} // namespace psdf
