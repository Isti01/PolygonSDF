#include "GuiStateEditorConsumer.h"
#include "../Core/PublishedEvent.h"
#include "../PublishedEvent/HideGuiPublishedEvent.h"
#include "../PublishedEvent/ShowGuiPublishedEvent.h"

using namespace psdf;

GuiStateEditorConsumer::SharedPtr GuiStateEditorConsumer::create()
{
    return SharedPtr(new GuiStateEditorConsumer());
}

void GuiStateEditorConsumer::accept(const EditorEvent::SharedPtr &pEvent)
{
    if (auto pPublishedEvent = std::dynamic_pointer_cast<EditorPublishedEvent>(pEvent))
    {
        if (std::dynamic_pointer_cast<ShowGuiPublishedEvent>(pPublishedEvent->getEvent()))
        {
            mIsGuiEnabled = true;
        }
        else if (std::dynamic_pointer_cast<HideGuiPublishedEvent>(pPublishedEvent->getEvent()))
        {
            mIsGuiEnabled = false;
        }
    }
}

bool GuiStateEditorConsumer::isGuiEnabled() const
{
    return mIsGuiEnabled;
}
