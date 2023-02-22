#include "VertexMoveInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/Deferred.h"
#include "../../Command/UpdatePointStackCommand.h"
#include "../VisualEditorConstants.h"

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
    float4x4 transform = mpPolygonRenderer->getTransform();
    auto mappedMousePos = CoordinateUtil::screenToSceneSpaceCoordinate(transform, mousePos);
    auto points = mpActivePolygon->getPoints();
    auto closestScenePoint = CoordinateUtil::findClosestPointIndex(points, mappedMousePos);
    if (!closestScenePoint)
    {
        return;
    }

    auto closestPoint = points.at(*closestScenePoint).getCoordinates();
    auto distance = glm::distance(mousePos, CoordinateUtil::sceneToScreenSpaceCoordinate(transform, closestPoint));
    if (distance > VisualEditorConstants::kSelectionDistanceThreshold)
    {
        return;
    }

    mSelectedVertexIndex = *closestScenePoint;
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
