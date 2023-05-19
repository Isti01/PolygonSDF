#include "ClearHistoryEditorTransformation.h"
#include "../Command/SetShapeStackCommand.h"

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
        pEditorStack->push(SetShapeStackCommand::create(top->pShape));
    }
}

std::string ClearHistoryEditorTransformation::getName() const
{
    return "ClearHistoryEditorTransformation";
}
