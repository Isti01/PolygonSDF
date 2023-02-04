#include "UndoEditorTransformation.h"

using namespace psdf;

EditorTransformation::SharedPtr UndoEditorTransformation::create()
{
    return EditorTransformation::SharedPtr(new UndoEditorTransformation());
}

void UndoEditorTransformation::transform(EditorStack::SharedPtr &pEditorStack)
{
    if (pEditorStack->getSize() > 0)
    {
        pEditorStack->pop();
    }
}
