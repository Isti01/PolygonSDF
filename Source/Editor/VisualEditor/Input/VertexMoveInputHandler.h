#pragma once

#include "../../Aggregator/PolygonPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "DragMouseInputHandler.h"
#include "MouseInputHandler.h"

namespace psdf
{

class VertexMoveInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<VertexMoveInputHandler>;

    static SharedPtr create(Editor::SharedPtr pEditor);
    void resetInputState() override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    VertexMoveInputHandler(Editor::SharedPtr pEditor);

  private:
    void updateSelectedPolygon(const Polygon::SharedPtr &pPolygon);

  private:
    Editor::SharedPtr mpEditor;
    DragMouseInputHandler::SharedPtr mpDragHandler;
    Polygon::SharedPtr mpActivePolygon = nullptr;
    PolygonPeekingEditorAggregator::SharedPtr mpPolygonAggregator;
};

} // namespace psdf
