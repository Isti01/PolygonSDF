#pragma once

#include "../Consumer/EventMenuEditorConsumer.h"
#include "../Core/Editor.h"
#include "EventMenuGui.h"
#include "GuiEditorMenu.h"

namespace psdf
{
using namespace Falcor;

class EventMenu: public GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<EventMenu>;
    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window) override;

    ~EventMenu();

  protected:
    EventMenu(Editor::SharedPtr pEditor);

  private:
    Editor::SharedPtr mpEditor;
    EventMenuGui::SharedPtr mpGui;
    EventMenuEditorConsumer::SharedPtr mpConsumer;
};

} // namespace psdf
