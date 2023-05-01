#pragma once

#include "../../../Polygon/Polygon.h"
#include "../../RenderObject.h"
#include "../PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class PolygonOutlineRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<PolygonOutlineRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState, const float4 &color = float4(1));

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void setColor(const float4 &color);
    float4 getColor() const;

  protected:
    PolygonOutlineRenderer(GraphicsState::SharedPtr pGraphicsState, const float4 &color = float4(1));

    void transformImpl() override;
    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const PolygonRendererProperty &rendererProperty) override;

  private:
    void uploadColor();

  private:
    bool mEnabled = true;
    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    RenderObject::SharedPtr mpRenderObject = nullptr;
    float4 mColor;
};

} // namespace psdf
