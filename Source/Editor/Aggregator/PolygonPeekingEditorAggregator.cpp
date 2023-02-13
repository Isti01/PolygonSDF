#include "PolygonPeekingEditorAggregator.h"

using namespace psdf;

PolygonPeekingEditorAggregationResult::PolygonPeekingEditorAggregationResult(Polygon::SharedPtr pPolygon)
    : mpPolygon(std::move(pPolygon))
{
}

PolygonPeekingEditorAggregationResult::SharedPtr PolygonPeekingEditorAggregationResult::create(
    Polygon::SharedPtr pPolygon)
{
    return SharedPtr(new PolygonPeekingEditorAggregationResult(std::move(pPolygon)));
}

PolygonPeekingEditorAggregator::SharedPtr PolygonPeekingEditorAggregator::create()
{
    return SharedPtr(new PolygonPeekingEditorAggregator());
}

Polygon::SharedPtr PolygonPeekingEditorAggregationResult::getPolygon() const
{
    return mpPolygon;
}

PolygonPeekingEditorAggregationResult::SharedPtr PolygonPeekingEditorAggregator::peekEditor(
    const Editor::SharedPtr &pEditor)
{
    auto aggregationResult = pEditor->reduce(this->shared_from_this());
    return std::dynamic_pointer_cast<PolygonPeekingEditorAggregationResult>(aggregationResult);
}

EditorAggregationResult::SharedPtr PolygonPeekingEditorAggregator::reduce(const EditorStack::SharedPtr &pEditorStack)
{
    auto topPolygon = pEditorStack->peek().value_or(StackEntry::kEmptyStackEntry).polygon;
    return PolygonPeekingEditorAggregationResult::create(topPolygon);
}
