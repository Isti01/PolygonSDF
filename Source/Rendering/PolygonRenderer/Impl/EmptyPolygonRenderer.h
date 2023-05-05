#pragma once

#include "../PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class EmptyPolygonRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<EmptyPolygonRenderer>;
    static SharedPtr create();

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    float4x4 getTransform() const override;

  protected:
    EmptyPolygonRenderer() = default;

    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void transformImpl() override;
    void setPropertyImpl(const PolygonRendererProperty &rendererProperty) override;
};

} // namespace psdf
