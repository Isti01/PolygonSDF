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
    SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pModifiedDepthState, GraphicsState::SharedPtr pSimpleMeshState);

    void transformImpl() override;
    void init() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;

    void setModifiedDepthProgramAsActive();
    void setSimpleMeshProgramAsActive();

    static constexpr double kMinCutDistanceFromOrigin = 10;

    size_t mPointsToCutAround = 100;

    GraphicsState::SharedPtr mpActiveState = nullptr;
    GraphicsVars::SharedPtr mpActiveProgramVars = nullptr;

    GraphicsState::SharedPtr mpModifiedDepthState = nullptr;
    GraphicsVars::SharedPtr mpModifiedDepthProgramVars = nullptr;

    GraphicsState::SharedPtr mpSimpleMeshState = nullptr;
    GraphicsVars::SharedPtr mpSimpleMeshProgramVars = nullptr;

    RenderObject::SharedPtr mpRenderObject = nullptr;
};

} // namespace psdf
