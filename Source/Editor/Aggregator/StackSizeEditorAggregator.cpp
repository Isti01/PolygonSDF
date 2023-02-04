#include "StackSizeEditorAggregator.h"

using namespace psdf;

StackSizeEditorAggregationResult::StackSizeEditorAggregationResult(size_t size) : mSize(size)
{
}

StackSizeEditorAggregationResult::SharedPtr StackSizeEditorAggregationResult::create(size_t size)
{
    return StackSizeEditorAggregationResult::SharedPtr(new StackSizeEditorAggregationResult(size));
}

size_t StackSizeEditorAggregationResult::getSize() const
{
    return mSize;
}

StackSizeEditorAggregator::SharedPtr StackSizeEditorAggregator::create()
{
    return StackSizeEditorAggregator::SharedPtr(new StackSizeEditorAggregator());
}

StackSizeEditorAggregationResult::SharedPtr StackSizeEditorAggregator::getEditorStackSize(
    const Editor::SharedPtr &pEditor)
{
    auto aggregationResult = pEditor->reduce(this->shared_from_this());
    return std::dynamic_pointer_cast<StackSizeEditorAggregationResult>(aggregationResult);
}

EditorAggregationResult::SharedPtr StackSizeEditorAggregator::reduce(const EditorStack::SharedPtr &pEditorStack)
{
    return StackSizeEditorAggregationResult::create(pEditorStack->getSize());
}
