#include "EventMenuEditorConsumer.h"

using namespace psdf;

EventMenuEditorConsumer::SharedPtr EventMenuEditorConsumer::create(EventMenuGui::SharedPtr pEventMenu)
{
    return SharedPtr(new EventMenuEditorConsumer(std::move(pEventMenu)));
}

EventMenuEditorConsumer::EventMenuEditorConsumer(EventMenuGui::SharedPtr pEventMenu)
    : mpEventMenu(std::move(pEventMenu))
{
}

void EventMenuEditorConsumer::accept(const EditorEvent::SharedPtr &pEvent)
{
    mpEventMenu->addNewEvent(pEvent);
}
