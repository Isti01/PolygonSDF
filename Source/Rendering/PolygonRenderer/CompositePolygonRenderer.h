#pragma once

#include "PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class CompositePolygonRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<CompositePolygonRenderer>;

    CompositePolygonRenderer(std::vector<PolygonRenderer::SharedPtr> renderers);

    void setPolygon(const Polygon::SharedPtr &pPolygon) override;
    void setFbo(const Fbo::SharedPtr &pFbo) const override;

  protected:
    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) const override;

  private:
    std::vector<PolygonRenderer::SharedPtr> mRenderers;
};

} // namespace psdf
