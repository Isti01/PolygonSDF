#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "../Input/DragMouseInputHandler.h"
#include "../Input/MouseInputHandler.h"

#include <Falcor.h>

namespace psdf
{

class Presenter : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<Presenter>;

    Presenter(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr outputRenderer);

    virtual void render(RenderContext *pRenderContext, const Fbo::SharedPtr &pTargetFbo) = 0;
    void resetTransform();
    void resetInputState();

  protected:
    float getMappedScale() const;
    void updatePolygon();
    virtual void transformPresenter() = 0;

  protected:
    static constexpr float mScaleSpeed = .1f;
    static constexpr float2 mRotationSpeed{-glm::pi<float>() * 1.5, glm::pi<float>() * 1.5};
    static constexpr float2 mTranslationSpeed{-1.0f, 1.0f};

    float mScale = 4;
    float2 mRotation{0};
    float2 mTranslation{0, 0};

    DragMouseInputHandler::SharedPtr mpDragHandler;
    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    PolygonRenderer::SharedPtr mpRenderer;
    Polygon::SharedPtr mpPolygon;
};

} // namespace psdf
