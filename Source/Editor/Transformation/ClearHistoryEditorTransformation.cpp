#include "ClearHistoryEditorTransformation.h"
#include "../Command/SetPolygonStackCommand.h"

using namespace psdf;

EditorTransformation::SharedPtr ClearHistoryEditorTransformation::create()
{
    return EditorTransformation::SharedPtr(new ClearHistoryEditorTransformation());
}

void ClearHistoryEditorTransformation::transform(EditorStack::SharedPtr &pEditorStack)
{
    if (auto top = pEditorStack->peek())
    {
        pEditorStack->clear();
        pEditorStack->push(SetPolygonStackCommand::create(top->polygon));
    }
}
