#pragma once

#include "../Consumer/VisualEditorStateChangeEditorConsumer.h"
#include "../Core/Editor.h"
#include "GuiEditorMenu.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class GuiEditor
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditor>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void render(Gui::Window &window);

    ~GuiEditor();

  protected:
    GuiEditor(Editor::SharedPtr pEditor);

  private:
    Editor::SharedPtr mpEditor;
    VisualEditorStateChangeEditorConsumer::SharedPtr mpStateChangeConsumer;
    std::vector<GuiEditorMenu::SharedPtr> menus;
};

} // namespace psdf
