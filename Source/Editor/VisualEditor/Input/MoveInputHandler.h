#pragma once

#include "../../../Rendering/ShapeRenderer/ShapeRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "DragMouseInputHandler.h"
#include "MouseInputHandler.h"

namespace psdf
{

class MoveStrategy
{
  public:
    using SharedPtr = std::shared_ptr<MoveStrategy>;

    virtual StackCommand::SharedPtr createCommand(size_t outlineInd, size_t vertexInd, Vertex prevPos,
                                                  Vertex newPos) = 0;
};

class MoveInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<MoveInputHandler>;

    static SharedPtr create(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                            ShapeRenderer::SharedPtr pPolygonRenderer);
    void resetInputState() override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    MoveInputHandler(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                     ShapeRenderer::SharedPtr pPolygonRenderer);

  private:
    void updateSelectedPolygon(StackEntry topStackEntry);
    void selectClosestVertex(float2 mousePos);
    void moveSelectedVertex(float2 mousePos);

  private:
    std::optional<std::pair<size_t, size_t>> mSelectedVertexIndex = std::nullopt;

    MoveStrategy::SharedPtr mpMoveStrategy;
    Editor::SharedPtr mpEditor = nullptr;
    DragMouseInputHandler::SharedPtr mpDragHandler = nullptr;
    Shape::SharedPtr mpActiveShape = nullptr;
    StackPeekingEditorAggregator::SharedPtr mpPolygonAggregator = nullptr;
    ShapeRenderer::SharedPtr mpShapeRenderer = nullptr;
    StackCommand::SharedPtr mpLastCommand = nullptr;
};

class PointUpdateMoveStrategy : public MoveStrategy
{
  public:
    static SharedPtr create();

    StackCommand::SharedPtr createCommand(size_t outlineInd, size_t vertexInd, Vertex prevPos, Vertex newPos) override;

  protected:
    PointUpdateMoveStrategy() = default;
};

class OutlineMoveStrategy : public MoveStrategy
{
  public:
    static SharedPtr create();

    StackCommand::SharedPtr createCommand(size_t outlineInd, size_t vertexInd, Vertex prevPos, Vertex newPos) override;

  protected:
    OutlineMoveStrategy() = default;
};

} // namespace psdf
