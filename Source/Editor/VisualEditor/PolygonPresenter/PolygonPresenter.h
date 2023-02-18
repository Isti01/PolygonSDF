#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../../Aggregator/PolygonPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "../Input/DragMouseInputHandler.h"
#include "../Input/MouseInputHandler.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class PolygonPresenter : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<PolygonPresenter>;

    static SharedPtr create(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo);

    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void resetInputState() override;

  protected:
    PolygonPresenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

    void updatePolygon();

  private:
    void transformPolygonRenderer();
    float getMappedScale() const;

  private:
    float mScale = .5f;
    float mScaleSpeed = .1f;

    float2 mTranslation{.0f};
    float2 mTranslationSpeed{1.0f, -1.0f};

    Editor::SharedPtr mpEditor;
    PolygonPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    PolygonRenderer::SharedPtr mpRenderer;
    Polygon::SharedPtr mpPolygon;
    DragMouseInputHandler::SharedPtr mpDragHandler;
};

} // namespace psdf
