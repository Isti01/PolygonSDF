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
    void setPolygon(const Polygon::SharedPtr &pPolygon) override;

  protected:
    SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState);

    static double getMaxDistanceFromPointInPolygon(const Point &point, const Polygon::SharedPtr &pPolygon);
    void transformImpl() override;
    void init() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const PolygonRendererProperty &rendererProperty) override;

    static constexpr double kMinCutDistanceFromOrigin = 10;

    size_t mPointsToCutAround = 100;

    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    RenderObject::SharedPtr mpRenderObject = nullptr;
};

} // namespace psdf
