#pragma once

#include "../../../Polygon/Polygon.h"
#include "../../RenderObject.h"

#include "../PolygonRenderer.h"
#include "Falcor.h"

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmOutputRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmOutputRenderer>;

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;

  protected:
    SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState);

    static double getMaxDistanceFromOriginInPolygon(const Polygon::SharedPtr &pPolygon);
    void transformImpl() override;
    void init() override;
    void renderImpl(RenderContext *pRenderContext) override;

    static constexpr size_t kPointsToCutAround = 100;
    static constexpr double kMinCutDistanceFromOrigin = 10;

    uint32_t mFboWidth = 0;
    uint32_t mFboHeight = 0;

    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    RenderObject::SharedPtr mpRenderObject = nullptr;
};

} // namespace psdf
