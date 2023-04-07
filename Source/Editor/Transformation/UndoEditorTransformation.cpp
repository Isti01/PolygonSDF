#include "UndoEditorTransformation.h"

using namespace psdf;

EditorTransformation::SharedPtr UndoEditorTransformation::create()
{
    return EditorTransformation::SharedPtr(new UndoEditorTransformation());
}

void UndoEditorTransformation::transform(EditorStack::SharedPtr &pEditorStack)
{
    if (pEditorStack->getSize() > 1)
    {
        pEditorStack->pop();
    }
}

std::string UndoEditorTransformation::getName() const
{
    return "UndoEditorTransformation";
}
