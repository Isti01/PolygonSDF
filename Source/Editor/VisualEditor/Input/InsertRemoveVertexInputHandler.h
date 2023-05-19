#pragma once

#include "../../../Rendering/ShapeRenderer/ShapeRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "MouseInputHandler.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class InsertRemoveVertexInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<InsertRemoveVertexInputHandler>;
    static SharedPtr create(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr pRenderer);

    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void resetInputState() override;

  protected:
    InsertRemoveVertexInputHandler(Editor::SharedPtr pEditor, ShapeRenderer::SharedPtr pRenderer);

  private:
    void insertNextToClosest(float2 position);
    size_t findIndexToInsert(float2 vertexPosition, size_t closestVertexIndex, const Shape::Vertices &points);

    bool removeVertexIfCloseEnough(float2 position);

  private:
    Editor::SharedPtr mpEditor;
    ShapeRenderer::SharedPtr mpRenderer;
    StackPeekingEditorAggregator::SharedPtr mpAggregator;
};

} // namespace psdf
