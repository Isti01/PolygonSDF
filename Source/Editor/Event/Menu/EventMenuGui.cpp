#include "EventMenuGui.h"
#include "../../../Util/WithImGuiId.h"

using namespace psdf;
using namespace Falcor;

EventMenuGui::SharedPtr EventMenuGui::create()
{
    return SharedPtr(new EventMenuGui());
}

void EventMenuGui::renderGui(Gui *pGui)
{
    Gui::Window window(pGui, "Event Menu");

    for (const auto &event : mEvents)
    {
        window.text(event->getName());
    }
}

void EventMenuGui::addNewEvent(EditorEvent::SharedPtr pEvent)
{
    mEvents.emplace(mEvents.begin(), std::move(pEvent));
}
