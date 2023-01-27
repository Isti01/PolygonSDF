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

class EditorAggregation
{
  public:
    using SharedPtr = std::shared_ptr<EditorAggregation>;

    virtual EditorAggregationResult::SharedPtr reduce(const EditorStack::SharedPtr &pEditorStack) = 0;

    virtual ~EditorAggregation() = default;
};

} // namespace psdf
