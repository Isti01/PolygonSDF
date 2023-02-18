#include "VertexMoveInputHandler.h"
#include "../../../Util/Deferred.h"

using namespace psdf;

VertexMoveInputHandler::SharedPtr VertexMoveInputHandler::create(Editor::SharedPtr pEditor)
{
    return VertexMoveInputHandler::SharedPtr(new VertexMoveInputHandler(std::move(pEditor)));
}

VertexMoveInputHandler::VertexMoveInputHandler(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpDragHandler(DragMouseInputHandler::create()),
      mpPolygonAggregator(PolygonPeekingEditorAggregator::create())
{
}

bool VertexMoveInputHandler::onMouseEvent(const Falcor::MouseEvent &mouseEvent)
{
    updateSelectedPolygon(mpPolygonAggregator->peekEditor(mpEditor)->getPolygon());
    if (!mpActivePolygon)
    {
        return false;
    }

    if (!mpDragHandler->onMouseEvent(mouseEvent))
    {
        return false;
    }

    if (mpDragHandler->isDragging())
    {
    }
    else
    {
    }

    return false;
}

void VertexMoveInputHandler::resetInputState()
{
    mpDragHandler->resetInputState();
}

void VertexMoveInputHandler::updateSelectedPolygon(const Polygon::SharedPtr &pPolygon)
{
    if (mpActivePolygon == pPolygon)
    {
        return;
    }

    mpActivePolygon = pPolygon;
    mpDragHandler->resetInputState();
}
