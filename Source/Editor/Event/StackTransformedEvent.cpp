#include "StackTransformedEvent.h"

using namespace psdf;

EditorEvent::SharedPtr StackTransformedEvent::create(const Editor::SharedPtr &pEditor,
                                                     const EditorTransformation::SharedPtr &pTransformation)
{
    return SharedPtr(new StackTransformedEvent(pEditor, pTransformation));
}

StackTransformedEvent::StackTransformedEvent(Editor::SharedPtr pEditor, EditorTransformation::SharedPtr pTransformation)
    : mpEditor(std::move(pEditor)), mpTransformation(std::move(pTransformation))

{
}

EditorTransformation::SharedPtr StackTransformedEvent::getTransformation() const
{
    return mpTransformation;
}

std::string StackTransformedEvent::getName() const
{
    return "StackTransformedEvent";
}
