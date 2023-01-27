#pragma once

#include "Editor.h"
#include "EditorCommand.h"
#include <memory>

namespace psdf
{

class EditorSupplier
{
  public:
    using SharedPtr = std::shared_ptr<EditorSupplier>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void dispatchCommand(EditorCommand::SharedPtr &pCommand);

    virtual ~EditorSupplier() = default;

  protected:
    EditorSupplier(Editor::SharedPtr pEditor);

  public:
    Editor::SharedPtr mpEditor;
};

} // namespace psdf
