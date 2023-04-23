#pragma once

#include "../../../Rendering/PolygonRenderer/Impl/SdfAlgorithmPointRegionRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../Input/DragMouseInputHandler.h"
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
    void resetInputState() override;

  protected:
    SdfAlgorithmOutputPresenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr outputRenderer);

    void updatePolygon();

  private:
    void resetTransform();
    void transformPresenter();
    float getMappedScale() const;

  private:
    static constexpr float mScaleSpeed = .1f;
    static constexpr float2 mRotationSpeed{-glm::pi<float>(), -glm::pi<float>()};

    float mScale = 3.5;
    float2 mRotation{0};

    Editor::SharedPtr mpEditor;
    PolygonRenderer::SharedPtr mpRenderer;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    Polygon::SharedPtr mpPolygon;
    DragMouseInputHandler::SharedPtr mpDragHandler;
};

} // namespace psdf
