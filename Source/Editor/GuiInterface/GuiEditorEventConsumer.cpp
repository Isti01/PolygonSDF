#include "GuiEditorEventConsumer.h"
#include "../Event/NewStackCommandEvent.h"

using namespace psdf;

GuiEditorEventConsumer::SharedPtr GuiEditorEventConsumer::create()
{
    return SharedPtr(new GuiEditorEventConsumer());
}

void GuiEditorEventConsumer::accept(const EditorEvent::SharedPtr &pEvent)
{
    if (auto newCommandEvent = std::dynamic_pointer_cast<NewStackCommandEvent>(pEvent)) {
    }
}
