#pragma once

#include "EditorStack.h"
#include <memory>

namespace psdf
{

class EditorAggregationResult
{
  public:
    using SharedPtr = std::shared_ptr<EditorAggregationResult>;

    virtual ~EditorAggregationResult() = default;

  protected:
    EditorAggregationResult() = default;
};

class EditorAggregator
{
  public:
    using SharedPtr = std::shared_ptr<EditorAggregator>;

    virtual EditorAggregationResult::SharedPtr reduce(const EditorStack::SharedPtr &pEditorStack) = 0;

    virtual ~EditorAggregator() = default;
};

} // namespace psdf
