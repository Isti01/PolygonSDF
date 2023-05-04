#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "../Input/DragMouseInputHandler.h"
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

    void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo);

    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void resetInputState() override;
    void resetTransform() override;

  protected:
    PolygonPresenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

    void updatePolygon();

  private:
    void transformPolygonRenderer();
    float getMappedScale() const;

  private:
    float mScale = 4;
    float mScaleSpeed = .1f;

    float2 mTranslation{0, 0};
    float2 mTranslationSpeed{-1.0f, 1.0f};

    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    PolygonRenderer::SharedPtr mpRenderer;
    Polygon::SharedPtr mpPolygon;
    DragMouseInputHandler::SharedPtr mpDragHandler;
};

} // namespace psdf
