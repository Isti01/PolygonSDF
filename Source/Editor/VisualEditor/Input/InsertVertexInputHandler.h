#pragma once

#include "../../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../../Aggregator/StackPeekingEditorAggregator.h"
#include "../../Core/Editor.h"
#include "MouseInputHandler.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class InsertVertexInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<InsertVertexInputHandler>;
    static SharedPtr create(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void resetInputState() override;

  protected:
    InsertVertexInputHandler(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer);

  private:
    void insertNextToClosest(float2 position);
    size_t findIndexToInsert(float2 vertexPosition, size_t closestVertexIndex, const Polygon::Points &points);

  private:
    Editor::SharedPtr mpEditor;
    PolygonRenderer::SharedPtr mpRenderer;
    StackPeekingEditorAggregator::SharedPtr mpAggregator;
};

} // namespace psdf
