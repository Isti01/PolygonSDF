#include "StackPeekingEditorAggregator.h"

using namespace psdf;

StackPeekingEditorAggregationResult::StackPeekingEditorAggregationResult(StackEntry stackEntry)
    : mStackEntry(std::move(stackEntry))
{
}

StackPeekingEditorAggregationResult::SharedPtr StackPeekingEditorAggregationResult::create(StackEntry stackEntry)
{
    return SharedPtr(new StackPeekingEditorAggregationResult(std::move(stackEntry)));
}

StackPeekingEditorAggregator::SharedPtr StackPeekingEditorAggregator::create()
{
    return SharedPtr(new StackPeekingEditorAggregator());
}

StackEntry StackPeekingEditorAggregationResult::getEntry() const
{
    return mStackEntry;
}

StackPeekingEditorAggregationResult::SharedPtr StackPeekingEditorAggregator::peekEditor(
    const Editor::SharedPtr &pEditor)
{
    auto aggregationResult = pEditor->reduce(this->shared_from_this());
    return std::dynamic_pointer_cast<StackPeekingEditorAggregationResult>(aggregationResult);
}

EditorAggregationResult::SharedPtr StackPeekingEditorAggregator::reduce(const EditorStack::SharedPtr &pEditorStack)
{
    auto top = pEditorStack->peek().value_or(StackEntry::kEmptyStackEntry);
    return StackPeekingEditorAggregationResult::create(top);
}
