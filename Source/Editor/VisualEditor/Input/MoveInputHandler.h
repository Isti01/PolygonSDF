#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
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

    virtual StackCommand::SharedPtr createCommand(size_t groupInd, size_t vertexInd, Point prevPos, Point newPos) = 0;
};

class MoveInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<MoveInputHandler>;

    static SharedPtr create(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                            PolygonRenderer::SharedPtr pPolygonRenderer);
    void resetInputState() override;
    bool onMouseEvent(const MouseEvent &mouseEvent) override;

  protected:
    MoveInputHandler(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                     PolygonRenderer::SharedPtr pPolygonRenderer);

  private:
    void updateSelectedPolygon(StackEntry topStackEntry);
    void selectClosestVertex(float2 mousePos);
    void moveSelectedVertex(float2 mousePos);

  private:
    std::optional<std::pair<size_t, size_t>> mSelectedVertexIndex = std::nullopt;

    MoveStrategy::SharedPtr mpMoveStrategy;
    Editor::SharedPtr mpEditor = nullptr;
    DragMouseInputHandler::SharedPtr mpDragHandler = nullptr;
    Polygon::SharedPtr mpActivePolygon = nullptr;
    StackPeekingEditorAggregator::SharedPtr mpPolygonAggregator = nullptr;
    PolygonRenderer::SharedPtr mpPolygonRenderer = nullptr;
    StackCommand::SharedPtr mpLastCommand = nullptr;
};

class PointUpdateMoveStrategy : public MoveStrategy
{
  public:
    static SharedPtr create();

    StackCommand::SharedPtr createCommand(size_t groupInd, size_t vertexInd, Point prevPos, Point newPos) override;

  protected:
    PointUpdateMoveStrategy() = default;
};

class GroupMoveStrategy : public MoveStrategy
{
  public:
    static SharedPtr create();

    StackCommand::SharedPtr createCommand(size_t groupInd, size_t vertexInd, Point prevPos, Point newPos) override;

  protected:
    GroupMoveStrategy() = default;
};

} // namespace psdf
