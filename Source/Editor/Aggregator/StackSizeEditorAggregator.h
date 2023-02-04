#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorAggregator.h"

#include <memory>

namespace psdf
{

class StackSizeEditorAggregationResult : public EditorAggregationResult
{
  public:
    using SharedPtr = std::shared_ptr<StackSizeEditorAggregationResult>;

    static SharedPtr create(size_t size);

    [[nodiscard]] size_t getSize() const;

  protected:
    StackSizeEditorAggregationResult(size_t size);

  private:
    size_t mSize;
};

class StackSizeEditorAggregator : public EditorAggregator,
                                  public std::enable_shared_from_this<StackSizeEditorAggregator>
{
  public:
    using SharedPtr = std::shared_ptr<StackSizeEditorAggregator>;

    static SharedPtr create();

    StackSizeEditorAggregationResult::SharedPtr getEditorStackSize(const Editor::SharedPtr &pEditor);

    EditorAggregationResult::SharedPtr reduce(const EditorStack::SharedPtr &pEditorStack) override;

  protected:
    StackSizeEditorAggregator() = default;
};

}; // namespace psdf
