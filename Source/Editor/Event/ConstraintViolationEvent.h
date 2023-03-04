#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorConstraint.h"
#include "../Core/EditorEvent.h"

namespace psdf
{

class ConstraintViolationEvent : public EditorEvent
{
  public:
    static SharedPtr create(const Editor::SharedPtr &pEditor, const EditorConstraint::SharedPtr &pConstraint,
                            const EditorCommand::SharedPtr &pCommand);

    std::string getName() const override;
    [[nodiscard]] EditorConstraint::SharedPtr getConstraint() const;
    [[nodiscard]] EditorCommand::SharedPtr getCommand() const;

  protected:
    ConstraintViolationEvent(Editor::SharedPtr pEditor, EditorConstraint::SharedPtr pConstraint,
                             EditorCommand::SharedPtr pCommand);

  private:
    Editor::SharedPtr mpEditor;
    EditorConstraint::SharedPtr mpConstraint;
    EditorCommand::SharedPtr mpCommand;
};

} // namespace psdf
