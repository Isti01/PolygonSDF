#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "DragMouseInputHandler.h"
#include "MouseInputHandler.h"

namespace psdf
{

class VertexMoveInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<VertexMoveInputHandler>;

    static SharedPtr create(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pPolygonRenderer);
    void resetInputState() override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    VertexMoveInputHandler(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pPolygonRenderer);

  private:
    void updateSelectedPolygon(StackEntry topStackEntry);
    void selectClosestVertex(float2 mousePos);
    void moveSelectedVertex(float2 mousePos);

  private:
    std::optional<size_t> mSelectedVertexIndex = std::nullopt;

    Editor::SharedPtr mpEditor = nullptr;
    DragMouseInputHandler::SharedPtr mpDragHandler = nullptr;
    Polygon::SharedPtr mpActivePolygon = nullptr;
    StackPeekingEditorAggregator::SharedPtr mpPolygonAggregator = nullptr;
    PolygonRenderer::SharedPtr mpPolygonRenderer = nullptr;
    StackCommand::SharedPtr mpLastCommand = nullptr;
};

} // namespace psdf
