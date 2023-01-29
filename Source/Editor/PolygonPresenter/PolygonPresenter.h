#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../Core/EditorConsumer.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class PolygonPresenter : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<PolygonPresenter>;

    static SharedPtr create();

    void accept(const EditorEvent::SharedPtr &pEvent) override;
    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo);

    void setRenderer(const PolygonRenderer::SharedPtr &pRenderer);

protected:
    PolygonPresenter() = default;

    void updatePolygon(const Polygon::SharedPtr& pPolygon);

  private:
    PolygonRenderer::SharedPtr mpRenderer;
    Polygon::SharedPtr mpPolygon;
};

} // namespace psdf
