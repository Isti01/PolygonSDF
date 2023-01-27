#pragma once

#include "EditorStack.h"
#include <memory>

namespace psdf
{

class EditorAggregationResult
{
  public:
    using SharedPtr = std::shared_ptr<EditorAggregationResult>;

  protected:
    EditorAggregationResult() = default;
};

class EditorAggregation
{
  public:
    using SharedPtr = std::shared_ptr<EditorAggregation>;

    virtual EditorAggregationResult::SharedPtr reduce(const EditorStack::SharedPtr &pEditorStack) = 0;

  protected:
    EditorAggregation() = default;
};

} // namespace psdf
