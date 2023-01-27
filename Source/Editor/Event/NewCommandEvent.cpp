#include "NewCommandEvent.h"

using namespace psdf;

EditorEvent::SharedPtr NewCommandEvent::create(const Editor::SharedPtr &pEditor,
                                               const EditorCommand::SharedPtr &pCommand)
{
    return SharedPtr(new NewCommandEvent(pEditor, pCommand));
}

NewCommandEvent::NewCommandEvent(Editor::SharedPtr pEditor, EditorCommand::SharedPtr pCommand)
    : mpEditor(std::move(pEditor)), mpCommand(std::move(pCommand))
{
}

EditorCommand::SharedPtr NewCommandEvent::getCommand() const
{
    return mpCommand;
}
