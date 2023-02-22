#include "InsertRemoveVertexInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/IndexUtil.h"
#include "../../Command/DeletePointStackCommand.h"
#include "../../Command/InsertPointStackCommand.h"
#include "../VisualEditorConstants.h"

using namespace psdf;
using namespace Falcor;

InsertRemoveVertexInputHandler::SharedPtr InsertRemoveVertexInputHandler::create(Editor::SharedPtr pEditor,
                                                                                 PolygonRenderer::SharedPtr pRenderer)
{
    return SharedPtr(new InsertRemoveVertexInputHandler(std::move(pEditor), std::move(pRenderer)));
}

InsertRemoveVertexInputHandler::InsertRemoveVertexInputHandler(Editor::SharedPtr pEditor,
                                                               PolygonRenderer::SharedPtr pRenderer)
    : mpEditor(std::move(pEditor)), mpRenderer(std::move(pRenderer)),
      mpAggregator(StackPeekingEditorAggregator::create())
{
}

bool InsertRemoveVertexInputHandler::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mouseEvent.type != MouseEvent::Type::ButtonUp)
    {
        return false;
    }
    if (mouseEvent.button == Input::MouseButton::Left)
    {
        insertNextToClosest(mouseEvent.pos);
        return true;
    }
    if (mouseEvent.button == Input::MouseButton::Right)
    {
        return removeVertexIfCloseEnough(mouseEvent.pos);
    }

    return false;
}

void InsertRemoveVertexInputHandler::resetInputState()
{
}

void InsertRemoveVertexInputHandler::insertNextToClosest(float2 position)
{
    auto polygon = mpAggregator->peekEditor(mpEditor)->getEntry().polygon;
    if (!polygon)
    {
        return;
    }
    auto points = polygon->getPoints();
    auto vertexPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    std::optional<size_t> closestIndex = CoordinateUtil::findClosestPointIndex(points, vertexPosition);
    if (!closestIndex)
    {
        return;
    }

    size_t insertionIndex = findIndexToInsert(vertexPosition, *closestIndex, points);
    mpEditor->addCommand(InsertPointStackCommand::create(insertionIndex, vertexPosition));
}

size_t InsertRemoveVertexInputHandler::findIndexToInsert(float2 vertexPosition, size_t closestVertexIndex,
                                                         const Polygon::Points &points)
{
    size_t prevIndex = IndexUtil::prevIndex(points.size(), closestVertexIndex);
    float2 prevPoint = points.at(prevIndex).getCoordinates();
    size_t nextIndex = IndexUtil::nextIndex(points.size(), closestVertexIndex);
    float2 nextPoint = points.at(nextIndex).getCoordinates();

    if (glm::distance(vertexPosition, prevPoint) > glm::distance(vertexPosition, nextPoint))
    {
        return nextIndex;
    }
    return closestVertexIndex;
}

bool InsertRemoveVertexInputHandler::removeVertexIfCloseEnough(float2 position)
{
    auto polygon = mpAggregator->peekEditor(mpEditor)->getEntry().polygon;
    if (!polygon)
    {
        return false;
    }
    auto points = polygon->getPoints();
    float2 mousePosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    std::optional<size_t> closestIndex = CoordinateUtil::findClosestPointIndex(points, mousePosition);
    if (!closestIndex)
    {
        return false;
    }
    float closestPointDistance = glm::distance(mousePosition, points.at(*closestIndex).getCoordinates());
    if (closestPointDistance > VisualEditorConstants::kSelectionDistanceThreshold)
    {
        return false;
    }

    mpEditor->addCommand(DeletePointStackCommand::create(*closestIndex));
    return true;
}
