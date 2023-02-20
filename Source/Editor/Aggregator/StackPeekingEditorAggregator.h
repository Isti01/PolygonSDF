#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorAggregator.h"

namespace psdf
{

class StackPeekingEditorAggregationResult : public EditorAggregationResult
{
  public:
    using SharedPtr = std::shared_ptr<StackPeekingEditorAggregationResult>;

    static SharedPtr create(StackEntry stackEntry);

    [[nodiscard]] StackEntry getEntry() const;

  protected:
    StackPeekingEditorAggregationResult(StackEntry stackEntry);

  private:
    StackEntry mStackEntry;
};

class StackPeekingEditorAggregator : public EditorAggregator,
                                       public std::enable_shared_from_this<StackPeekingEditorAggregator>
{
  public:
    using SharedPtr = std::shared_ptr<StackPeekingEditorAggregator>;

    static SharedPtr create();

    StackPeekingEditorAggregationResult::SharedPtr peekEditor(const Editor::SharedPtr &pEditor);

    EditorAggregationResult::SharedPtr reduce(const EditorStack::SharedPtr &pEditorStack) override;

  protected:
    StackPeekingEditorAggregator() = default;
};

} // namespace psdf
