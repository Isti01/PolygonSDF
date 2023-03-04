#pragma once

#include "../Core/EditorCommand.h"
#include "../Core/EditorEvent.h"

namespace psdf
{

class UnknownCommandEvent : public EditorEvent
{
  public:
    static SharedPtr create(EditorCommand::SharedPtr pCommand);

    std::string getName() const override;

    [[nodiscard]] EditorCommand::SharedPtr getEditorCommand() const;

  protected:
    UnknownCommandEvent(EditorCommand::SharedPtr pCommand);

  private:
    EditorCommand::SharedPtr mpCommand;
};

} // namespace psdf
