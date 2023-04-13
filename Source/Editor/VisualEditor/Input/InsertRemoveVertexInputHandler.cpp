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
    auto polygons = polygon->getPolygons();
    auto vertexPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    auto closestIndex = CoordinateUtil::findClosestPointIndex(polygons, vertexPosition);
    if (!closestIndex)
    {
        return;
    }

    size_t groupIndex = closestIndex->first;
    size_t vertexIndex = closestIndex->second;
    size_t insertionIndex = findIndexToInsert(vertexPosition, vertexIndex, polygons[groupIndex].getPoints());
    mpEditor->addCommand(InsertPointStackCommand::create(groupIndex, insertionIndex, vertexPosition));
}

size_t InsertRemoveVertexInputHandler::findIndexToInsert(float2 vertexPosition, size_t closestVertexIndex,
                                                         const Polygon::Points &points)
{
    size_t prevIndex = IndexUtil::prevIndex(points.size(), closestVertexIndex);
    float2 prevPoint = points.at(prevIndex);
    size_t nextIndex = IndexUtil::nextIndex(points.size(), closestVertexIndex);
    float2 nextPoint = points.at(nextIndex);

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

    auto polygons = polygon->getPolygons();
    float2 mousePosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    auto closestIndex = CoordinateUtil::findClosestPointIndex(polygons, mousePosition);
    if (!closestIndex)
    {
        return false;
    }
    size_t vertexIndex = closestIndex->first;
    size_t groupIndex = closestIndex->second;
    float closestPointDistance = glm::distance(mousePosition, float2(polygons.at(groupIndex).getPoints()[vertexIndex]));
    if (closestPointDistance > VisualEditorConstants::kSelectionDistanceThreshold)
    {
        return false;
    }

    mpEditor->addCommand(DeletePointStackCommand::create(groupIndex, vertexIndex));
    return true;
}
