#include "InsertVertexInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/IndexUtil.h"
#include "../../Command/InsertPointStackCommand.h"

using namespace psdf;
using namespace Falcor;

InsertVertexInputHandler::SharedPtr InsertVertexInputHandler::create(Editor::SharedPtr pEditor,
                                                                     PolygonRenderer::SharedPtr pRenderer)
{
    return SharedPtr(new InsertVertexInputHandler(std::move(pEditor), std::move(pRenderer)));
}

InsertVertexInputHandler::InsertVertexInputHandler(Editor::SharedPtr pEditor, PolygonRenderer::SharedPtr pRenderer)
    : mpEditor(std::move(pEditor)), mpRenderer(std::move(pRenderer)),
      mpAggregator(StackPeekingEditorAggregator::create())
{
}

bool InsertVertexInputHandler::onMouseEvent(const MouseEvent &mouseEvent)
{
    if (mouseEvent.type == MouseEvent::Type::ButtonUp)
    {
        insertNextToClosest(mouseEvent.pos);
        return true;
    }

    return false;
}

void InsertVertexInputHandler::resetInputState()
{
}

void InsertVertexInputHandler::insertNextToClosest(float2 position)
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

size_t InsertVertexInputHandler::findIndexToInsert(float2 vertexPosition, size_t closestVertexIndex,
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
