#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorAggregator.h"

namespace psdf
{

class PolygonPeekingEditorAggregationResult : public EditorAggregationResult
{
  public:
    using SharedPtr = std::shared_ptr<PolygonPeekingEditorAggregationResult>;

    static SharedPtr create(Polygon::SharedPtr pPolygon);

    [[nodiscard]] Polygon::SharedPtr getPolygon() const;

  protected:
    PolygonPeekingEditorAggregationResult(Polygon::SharedPtr pPolygon);

  private:
    Polygon::SharedPtr mpPolygon;
};

class PolygonPeekingEditorAggregator : public EditorAggregator,
                                       public std::enable_shared_from_this<PolygonPeekingEditorAggregator>
{
  public:
    using SharedPtr = std::shared_ptr<PolygonPeekingEditorAggregator>;

    static SharedPtr create();

    PolygonPeekingEditorAggregationResult::SharedPtr peekEditor(const Editor::SharedPtr &pEditor);

    EditorAggregationResult::SharedPtr reduce(const EditorStack::SharedPtr &pEditorStack) override;

  protected:
    PolygonPeekingEditorAggregator() = default;
};

} // namespace psdf
