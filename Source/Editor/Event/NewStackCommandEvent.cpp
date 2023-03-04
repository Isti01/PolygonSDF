#include "NewStackCommandEvent.h"

using namespace psdf;

EditorEvent::SharedPtr NewStackCommandEvent::create(const Editor::SharedPtr &pEditor,
                                                    const EditorCommand::SharedPtr &pCommand)
{
    return SharedPtr(new NewStackCommandEvent(pEditor, pCommand));
}

NewStackCommandEvent::NewStackCommandEvent(Editor::SharedPtr pEditor, EditorCommand::SharedPtr pCommand)
    : mpEditor(std::move(pEditor)), mpCommand(std::move(pCommand))
{
}

EditorCommand::SharedPtr NewStackCommandEvent::getCommand() const
{
    return mpCommand;
}

Editor::SharedPtr NewStackCommandEvent::getEditor() const
{
    return mpEditor;
}

std::string NewStackCommandEvent::getName() const
{
    std::stringstream ss;
    ss << "NewStackCommandEvent(" << mpCommand->getName() << ')';
    return ss.str();
}
