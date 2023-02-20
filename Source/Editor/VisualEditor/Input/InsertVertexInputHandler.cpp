#include "InsertVertexInputHandler.h"
#include "../../../Util/CoordinateUtil.h"
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

void InsertVertexInputHandler::insertNextToClosest(float2 position)
{
    auto polygon = mpAggregator->peekEditor(mpEditor)->getEntry().polygon;
    if (!polygon)
    {
        return;
    }

    auto newPosition = CoordinateUtil::screenToSceneSpaceCoordinate(mpRenderer->getTransform(), position);
    std::optional<size_t> index = CoordinateUtil::findClosestPointIndexInPolygon(polygon, newPosition);
    if (!index)
    {
        return;
    }

    mpEditor->addCommand(InsertPointStackCommand::create(*index, newPosition));
}

void InsertVertexInputHandler::resetInputState()
{
}
