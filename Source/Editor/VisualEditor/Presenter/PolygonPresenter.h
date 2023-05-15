#pragma once

#include "Presenter.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class PolygonPresenter : public Presenter
{
  public:
    using SharedPtr = std::shared_ptr<PolygonPresenter>;

    static SharedPtr create(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) override;

    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    PolygonPresenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

    void transformPresenter() override;
};

} // namespace psdf
