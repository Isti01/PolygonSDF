#pragma once

#include "../../Core/Editor.h"
#include "EventMenuEditorConsumer.h"
#include "EventMenuGui.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class EventMenu
{
  public:
    using SharedPtr = std::shared_ptr<EventMenu>;
    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui *pGui);

    ~EventMenu();

  protected:
    EventMenu(Editor::SharedPtr pEditor);

  private:
    Editor::SharedPtr mpEditor;
    EventMenuGui::SharedPtr mpGui;
    EventMenuEditorConsumer::SharedPtr mpConsumer;
};

} // namespace psdf
