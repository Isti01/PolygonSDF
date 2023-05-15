#pragma once

#include "Presenter.h"

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmOutputPresenter : public Presenter
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmOutputPresenter>;

    static SharedPtr create(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr outputRenderer);

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo);

    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    SdfAlgorithmOutputPresenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr outputRenderer);

    void transformPresenter() override;
};

} // namespace psdf
