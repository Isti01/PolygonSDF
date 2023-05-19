#include "MoveInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/Deferred.h"
#include "../../Command/MoveOutlineStackCommand.h"
#include "../../Command/UpdateVertexStackCommand.h"
#include "../VisualEditorConstants.h"

using namespace psdf;

MoveInputHandler::SharedPtr MoveInputHandler::create(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                                                     ShapeRenderer::SharedPtr pPolygonRenderer)
{
    return SharedPtr(new MoveInputHandler(std::move(strategy), std::move(pEditor), std::move(pPolygonRenderer)));
}

MoveInputHandler::MoveInputHandler(MoveStrategy::SharedPtr strategy, Editor::SharedPtr pEditor,
                                   ShapeRenderer::SharedPtr pPolygonRenderer)
    : mpMoveStrategy(std::move(strategy)), mpEditor(std::move(pEditor)), mpDragHandler(DragMouseInputHandler::create()),
      mpPolygonAggregator(StackPeekingEditorAggregator::create()), mpShapeRenderer(std::move(pPolygonRenderer))
{
}

bool MoveInputHandler::onMouseEvent(const Falcor::MouseEvent &mouseEvent)
{
    updateSelectedPolygon(mpPolygonAggregator->peekEditor(mpEditor)->getEntry());
    if (!mpActiveShape)
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
    float4x4 transform = mpShapeRenderer->getTransform();
    auto mappedMousePos = CoordinateUtil::screenToSceneSpaceCoordinate(transform, mousePos);
    auto outlines = mpActiveShape->getOutlines();
    auto closestScenePoint = CoordinateUtil::findClosestPointIndex(outlines, mappedMousePos);
    if (!closestScenePoint)
    {
        return;
    }

    auto closestPoint = outlines.at(closestScenePoint->first).getVertices()[closestScenePoint->second];
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
    auto newPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpShapeRenderer->getTransform(), mousePos);
    auto oldPosition = mpActiveShape->getOutlines()[groupIndex].getVertices()[vertIndex];
    mpEditor->addCommand(mpMoveStrategy->createCommand(groupIndex, vertIndex, oldPosition, Vertex(newPosition)));
    mpLastCommand = mpPolygonAggregator->peekEditor(mpEditor)->getEntry().pCommand;
}

void MoveInputHandler::resetInputState()
{
    mpDragHandler->resetInputState();
}

void MoveInputHandler::updateSelectedPolygon(StackEntry topStackEntry)
{
    if (mpActiveShape == topStackEntry.pShape)
    {
        return;
    }

    mpActiveShape = topStackEntry.pShape;
    if (topStackEntry.pCommand != mpLastCommand) // the polygon was updated from outside
    {
        mSelectedVertexIndex = std::nullopt;
        mpDragHandler->resetInputState();
    }
}

MoveStrategy::SharedPtr PointUpdateMoveStrategy::create()
{
    return SharedPtr(new PointUpdateMoveStrategy());
}

StackCommand::SharedPtr PointUpdateMoveStrategy::createCommand(size_t groupInd, size_t vertexInd, Vertex prevPos,
                                                               Vertex newPos)
{
    return UpdateVertexStackCommand::create(groupInd, vertexInd, newPos);
}

MoveStrategy::SharedPtr OutlineMoveStrategy::create()
{
    return SharedPtr(new OutlineMoveStrategy());
}

StackCommand::SharedPtr OutlineMoveStrategy::createCommand(size_t groupInd, size_t vertexInd, Vertex prevPos,
                                                         Vertex newPos)
{
    return MoveOutlineStackCommand::create(groupInd, prevPos, newPos);
}
