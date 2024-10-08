#include "InsertRemoveVertexInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
#include "../../../Util/IndexUtil.h"
#include "../../Command/DeleteVertexStackCommand.h"
#include "../../Command/InsertVertexStackCommand.h"
#include "../VisualEditorConstants.h"

using namespace psdf;
using namespace Falcor;

InsertRemoveVertexInputHandler::SharedPtr InsertRemoveVertexInputHandler::create(Editor::SharedPtr pEditor,
                                                                                 ShapeRenderer::SharedPtr pRenderer)
{
    return SharedPtr(new InsertRemoveVertexInputHandler(std::move(pEditor), std::move(pRenderer)));
}

InsertRemoveVertexInputHandler::InsertRemoveVertexInputHandler(Editor::SharedPtr pEditor,
                                                               ShapeRenderer::SharedPtr pRenderer)
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
    auto shape = mpAggregator->peekEditor(mpEditor)->getEntry().pShape;
    if (!shape)
    {
        return;
    }
    auto outlines = shape->getOutlines();
    auto vertexPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    auto closestIndex = CoordinateUtil::findClosestPointIndex(outlines, vertexPosition);
    if (!closestIndex)
    {
        return;
    }

    size_t outlineIndex = closestIndex->first;
    size_t vertexIndex = closestIndex->second;
    size_t insertionIndex = findIndexToInsert(vertexPosition, vertexIndex, outlines[outlineIndex].getVertices());
    mpEditor->addCommand(InsertVertexStackCommand::create(outlineIndex, insertionIndex, vertexPosition));
}

size_t InsertRemoveVertexInputHandler::findIndexToInsert(float2 vertexPosition, size_t closestVertexIndex,
                                                         const Shape::Vertices &points)
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
    auto shape = mpAggregator->peekEditor(mpEditor)->getEntry().pShape;
    if (!shape)
    {
        return false;
    }

    auto outlines = shape->getOutlines();
    float2 mousePosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    auto closestIndex = CoordinateUtil::findClosestPointIndex(outlines, mousePosition);
    if (!closestIndex)
    {
        return false;
    }
    size_t outlineIndex = closestIndex->first;
    size_t vertexIndex = closestIndex->second;
    float closestPointDistance =
        glm::distance(mousePosition, float2(outlines.at(outlineIndex).getVertices()[vertexIndex]));
    if (closestPointDistance > VisualEditorConstants::kSelectionDistanceThreshold)
    {
        return false;
    }

    mpEditor->addCommand(DeleteVertexStackCommand::create(outlineIndex, vertexIndex));
    return true;
}
