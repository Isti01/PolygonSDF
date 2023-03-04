#include "UnknownCommandEvent.h"
#include <sstream>

using namespace psdf;

EditorEvent::SharedPtr UnknownCommandEvent::create(EditorCommand::SharedPtr pCommand)
{
    return EditorEvent::SharedPtr(new UnknownCommandEvent(std::move(pCommand)));
}

UnknownCommandEvent::UnknownCommandEvent(EditorCommand::SharedPtr pCommand) : mpCommand(std::move(pCommand))
{
}

EditorCommand::SharedPtr UnknownCommandEvent::getEditorCommand() const
{
    return mpCommand;
}

std::string UnknownCommandEvent::getName() const
{
    std::stringstream ss;
    ss << "UnknownCommandEvent(" << mpCommand->getName() << ')';
    return ss.str();
}
