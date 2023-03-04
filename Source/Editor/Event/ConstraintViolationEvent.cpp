#include "ConstraintViolationEvent.h"
#include <utility>

using namespace psdf;

EditorEvent::SharedPtr ConstraintViolationEvent::create(const Editor::SharedPtr &pEditor,
                                                        const EditorConstraint::SharedPtr &pConstraint,
                                                        const EditorCommand::SharedPtr &pCommand)
{
    return EditorEvent::SharedPtr(new ConstraintViolationEvent(pEditor, pConstraint, pCommand));
}

ConstraintViolationEvent::ConstraintViolationEvent(Editor::SharedPtr pEditor, EditorConstraint::SharedPtr pConstraint,
                                                   EditorCommand::SharedPtr pCommand)
    : mpEditor(std::move(pEditor)), mpConstraint(std::move(pConstraint)), mpCommand(std::move(pCommand))
{
}

EditorConstraint::SharedPtr ConstraintViolationEvent::getConstraint() const
{
    return mpConstraint;
}

EditorCommand::SharedPtr ConstraintViolationEvent::getCommand() const
{
    return mpCommand;
}

std::string ConstraintViolationEvent::getName() const
{
    return "ConstraintViolationEvent";
}
