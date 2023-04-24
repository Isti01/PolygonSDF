#include "MoveInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/Deferred.h"
#include "../../Command/MoveGroupStackCommand.h"
#include "../../Command/UpdatePointStackCommand.h"
#include "../VisualEditorConstants.h"

using namespace psdf;

MoveInputHandler::SharedPtr MoveInputHandler::create(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                                                     PolygonRenderer::SharedPtr pPolygonRenderer)
{
    return SharedPtr(new MoveInputHandler(std::move(strategy), std::move(pEditor), std::move(pPolygonRenderer)));
}

MoveInputHandler::MoveInputHandler(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                                   PolygonRenderer::SharedPtr pPolygonRenderer)
    : mpMoveStrategy(std::move(strategy)), mpEditor(std::move(pEditor)), mpDragHandler(DragMouseInputHandler::create()),
      mpPolygonAggregator(StackPeekingEditorAggregator::create()), mpPolygonRenderer(std::move(pPolygonRenderer))
{
}

bool MoveInputHandler::onMouseEvent(const Falcor::MouseEvent &mouseEvent)
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

void MoveInputHandler::selectClosestVertex(float2 mousePos)
{
    float4x4 transform = mpPolygonRenderer->getTransform();
    auto mappedMousePos = CoordinateUtil::screenToSceneSpaceCoordinate(transform, mousePos);
    auto polygons = mpActivePolygon->getPolygons();
    auto closestScenePoint = CoordinateUtil::findClosestPointIndex(polygons, mappedMousePos);
    if (!closestScenePoint)
    {
        return;
    }

    auto closestPoint = polygons.at(closestScenePoint->first).getPoints()[closestScenePoint->second];
    auto distance = glm::distance(mousePos, CoordinateUtil::sceneToScreenSpaceCoordinate(transform, closestPoint));
    if (distance > VisualEditorConstants::kSelectionDistanceThreshold)
    {
        return;
    }

    mSelectedVertexIndex = *closestScenePoint;
}

void MoveInputHandler::moveSelectedVertex(float2 mousePos)
{
    if (!mSelectedVertexIndex)
    {
        return;
    }

    size_t groupIndex = mSelectedVertexIndex->first;
    size_t vertIndex = mSelectedVertexIndex->second;
    auto newPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpPolygonRenderer->getTransform(), mousePos);
    auto oldPosition = mpActivePolygon->getPolygons()[groupIndex].getPoints()[vertIndex];
    mpEditor->addCommand(mpMoveStrategy->createCommand(groupIndex, vertIndex, oldPosition, Point(newPosition)));
    mpLastCommand = mpPolygonAggregator->peekEditor(mpEditor)->getEntry().command;
}

void MoveInputHandler::resetInputState()
{
    mpDragHandler->resetInputState();
}

void MoveInputHandler::updateSelectedPolygon(StackEntry topStackEntry)
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

MoveStrategy::SharedPtr PointUpdateMoveStrategy::create()
{
    return SharedPtr(new PointUpdateMoveStrategy());
}

StackCommand::SharedPtr PointUpdateMoveStrategy::createCommand(size_t groupInd, size_t vertexInd, Point prevPos,
                                                               Point newPos)
{
    return UpdatePointStackCommand::create(groupInd, vertexInd, newPos);
}

MoveStrategy::SharedPtr GroupMoveStrategy::create()
{
    return SharedPtr(new GroupMoveStrategy());
}

StackCommand::SharedPtr GroupMoveStrategy::createCommand(size_t groupInd, size_t vertexInd, Point prevPos, Point newPos)
{
    return MoveGroupStackCommand::create(groupInd, prevPos, newPos);
}
