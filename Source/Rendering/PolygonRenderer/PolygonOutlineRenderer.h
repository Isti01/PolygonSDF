#pragma once

#include "../../Polygon/Polygon.h"
#include "../RenderObject.h"
#include "./PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class PolygonOutlineRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<PolygonOutlineRenderer>;
    void setFbo(const Fbo::SharedPtr &pFbo);

  protected:
    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) const override;

  private:
    GraphicsState::SharedPtr mpGraphicsState = nullptr;
    GraphicsVars::SharedPtr mpProgramVars = nullptr;
    RenderObject::SharedPtr mpRenderObject = nullptr;
};

} // namespace psdf
