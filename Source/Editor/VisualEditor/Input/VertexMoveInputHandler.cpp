#include "VertexMoveInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/Deferred.h"
#include "../../Command/UpdatePointStackCommand.h"

using namespace psdf;

VertexMoveInputHandler::SharedPtr VertexMoveInputHandler::create(Editor::SharedPtr pEditor,
                                                                 PolygonRenderer::SharedPtr pPolygonRenderer)
{
    return SharedPtr(new VertexMoveInputHandler(std::move(pEditor), std::move(pPolygonRenderer)));
}

VertexMoveInputHandler::VertexMoveInputHandler(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pPolygonRenderer)
    : mpEditor(std::move(pEditor)), mpDragHandler(DragMouseInputHandler::create()),
      mpPolygonAggregator(StackPeekingEditorAggregator::create()), mpPolygonRenderer(std::move(pPolygonRenderer))
{
}

bool VertexMoveInputHandler::onMouseEvent(const Falcor::MouseEvent &mouseEvent)
{
    updateSelectedPolygon(mpPolygonAggregator->peekEditor(mpEditor)->getEntry());
    if (!mpActivePolygon)
    {
        return false;
    }

    if (!mpDragHandler->onMouseEvent(mouseEvent))
    {
        return false;
    }

    if (mpDragHandler->isDragStarted() && !mSelectedVertexIndex)
    {
        selectClosestVertex(mouseEvent.pos);
        return true;
    }

    if (mpDragHandler->isDragging())
    {
        moveSelectedVertex(mouseEvent.pos);
        return true;
    }
    else // the mouse is released
    {
        moveSelectedVertex(mouseEvent.pos);
        mSelectedVertexIndex = std::nullopt;
        return true;
    }
}

void VertexMoveInputHandler::selectClosestVertex(float2 mousePos)
{
    auto points = mpActivePolygon->getPoints();
    float4x4 transform = mpPolygonRenderer->getTransform();
    auto iterator = std::min_element(points.begin(), points.end(), [mousePos, &transform](Point p1, Point p2) {
        auto d1 = glm::distance(mousePos, CoordinateUtil::sceneToScreenSpaceCoordinate(transform, p1.getCoordinates()));
        auto d2 = glm::distance(mousePos, CoordinateUtil::sceneToScreenSpaceCoordinate(transform, p2.getCoordinates()));
        return d1 < d2;
    });
    if (iterator == points.end())
    {
        return;
    }

    auto closestPoint = CoordinateUtil::sceneToScreenSpaceCoordinate(transform, iterator->getCoordinates());
    if (glm::distance(mousePos, closestPoint) > kSelectionDistanceThreshold)
    {
        return;
    }

    mSelectedVertexIndex = iterator - points.begin();
}

void VertexMoveInputHandler::moveSelectedVertex(float2 mousePos)
{
    if (!mSelectedVertexIndex)
    {
        return;
    }

    auto newPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpPolygonRenderer->getTransform(), mousePos);
    mpLastCommand = UpdatePointStackCommand::create(*mSelectedVertexIndex, Point(newPosition));
    mpEditor->addCommand(mpLastCommand);
}

void VertexMoveInputHandler::resetInputState()
{
    mpDragHandler->resetInputState();
}

void VertexMoveInputHandler::updateSelectedPolygon(StackEntry topStackEntry)
{
    if (mpActivePolygon == topStackEntry.polygon)
    {
        return;
    }

    mpActivePolygon = topStackEntry.polygon;
    if (topStackEntry.command != mpLastCommand) // the polygon was updated from outside
    {
        mSelectedVertexIndex = std::nullopt;
        mpDragHandler->resetInputState();
    }
}
