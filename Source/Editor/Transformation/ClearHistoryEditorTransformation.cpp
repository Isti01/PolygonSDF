#include "ClearHistoryEditorTransformation.h"
#include "../Command/SetPolygonStackCommand.h"

using namespace psdf;

EditorTransformation::SharedPtr ClearHistoryEditorTransformation::create()
{
    return EditorTransformation::SharedPtr(new ClearHistoryEditorTransformation());
}

void ClearHistoryEditorTransformation::transform(EditorStack::SharedPtr &pEditorStack)
{
    auto polygon = pEditorStack->peekPolygon();
    pEditorStack->clear();
    if (polygon != nullptr)
    {
        pEditorStack->push(SetPolygonStackCommand::create(polygon));
    }
}
