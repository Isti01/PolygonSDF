#include "ShowGuiPublishedEvent.h"

using namespace psdf;

ShowGuiPublishedEvent::SharedPtr ShowGuiPublishedEvent::create()
{
    return SharedPtr(new ShowGuiPublishedEvent());
}

std::string ShowGuiPublishedEvent::getName()
{
    return "ShowGuiPublishedEvent";
}
