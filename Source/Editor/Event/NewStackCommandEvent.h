#pragma once

#include "../Core/Editor.h"
#include "../Core/EditorEvent.h"

namespace psdf
{

class NewStackCommandEvent : public EditorEvent
{
  public:
    static SharedPtr create(const Editor::SharedPtr &pEditor, const EditorCommand::SharedPtr &pCommand);

    [[nodiscard]] EditorCommand::SharedPtr getCommand() const;
    [[nodiscard]] Editor::SharedPtr getEditor() const;

  protected:
    NewStackCommandEvent(Editor::SharedPtr pEditor, EditorCommand::SharedPtr pCommand);

  private:
    Editor::SharedPtr mpEditor;
    EditorCommand::SharedPtr mpCommand;
};

} // namespace psdf
