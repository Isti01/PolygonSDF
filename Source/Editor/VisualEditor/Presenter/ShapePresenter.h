#pragma once

#include "Presenter.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class ShapePresenter : public Presenter
{
  public:
    using SharedPtr = std::shared_ptr<ShapePresenter>;

    static SharedPtr create(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr pRenderer);

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) override;

    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    ShapePresenter(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr pRenderer);

    void transformPresenter() override;
};

} // namespace psdf
