#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../Aggregator/PolygonPeekingEditorAggregator.h"
#include "../Core/Editor.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class PolygonPresenter
{
  public:
    using SharedPtr = std::shared_ptr<PolygonPresenter>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo);

    void setRenderer(const PolygonRenderer::SharedPtr &pRenderer);

  protected:
    PolygonPresenter(Editor::SharedPtr pEditor);

    void updatePolygon();

  private:
    Editor::SharedPtr mpEditor;
    PolygonPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    PolygonRenderer::SharedPtr mpRenderer;
    Polygon::SharedPtr mpPolygon;
};

} // namespace psdf
