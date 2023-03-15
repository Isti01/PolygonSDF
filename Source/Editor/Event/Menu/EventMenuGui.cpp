#include "EventMenuGui.h"

using namespace psdf;
using namespace Falcor;

EventMenuGui::SharedPtr EventMenuGui::create()
{
    return SharedPtr(new EventMenuGui());
}

void EventMenuGui::renderGui(Gui *pGui)
{

    Gui::Window window(pGui, "Event Menu");

    if (window.button("Clear event history"))
    {
        mEvents.clear();
    }

    renderCumulatedEvents(window);
}

void EventMenuGui::addNewEvent(EditorEvent::SharedPtr pEvent)
{
    mEvents.emplace(mEvents.begin(), std::move(pEvent));
}

void EventMenuGui::renderCumulatedEvents(Gui::Window &window) const
{
    if (mEvents.empty())
    {
        return;
    }

    size_t groupCount = 1;
    std::string groupText = mEvents[0]->getName();

    for (int i = 1; i < mEvents.size(); i++)
    {
        std::string currentText = mEvents[i]->getName();
        if (groupText == currentText)
        {
            groupCount++;
        }
        else
        {
            window.text(getCumulatedText(groupCount, groupText));
            groupCount = 1;
            groupText = currentText;
        }
    }
    window.text(getCumulatedText(groupCount, groupText));
}

std::string EventMenuGui::getCumulatedText(size_t repeats, const std::string &text) const
{
    std::stringstream ss;
    if (repeats > 1)
    {
        ss << '(' << repeats << ") ";
    }
    ss << text;
    return ss.str();
}
