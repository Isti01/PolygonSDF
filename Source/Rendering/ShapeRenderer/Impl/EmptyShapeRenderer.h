#pragma once

#include "../ShapeRenderer.h"

namespace psdf
{
using namespace Falcor;

class EmptyShapeRenderer : public ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<EmptyShapeRenderer>;
    static SharedPtr create();

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    float4x4 getTransform() const override;

  protected:
    EmptyShapeRenderer() = default;

    void init() override;
    void uploadShapeData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void transformImpl() override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;
};

} // namespace psdf
