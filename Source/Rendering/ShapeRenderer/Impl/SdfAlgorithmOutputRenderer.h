#pragma once

#include "../../../Shape/Shape.h"
#include "../../RenderObject.h"

#include "../ShapeRenderer.h"
#include "Falcor.h"

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmOutputRenderer : public ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmOutputRenderer>;

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void setShape(const Shape::SharedPtr &pShape) override;

  protected:
    SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState);

    void transformImpl() override;
    void init() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;

    static constexpr double kMinCutDistanceFromOrigin = 10;

    size_t mPointsToCutAround = 100;

    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    RenderObject::SharedPtr mpRenderObject = nullptr;
};

} // namespace psdf
