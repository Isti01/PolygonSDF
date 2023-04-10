#include "HideGuiPublishedEvent.h"

using namespace psdf;

HideGuiPublishedEvent::SharedPtr HideGuiPublishedEvent::create()
{
    return SharedPtr(new HideGuiPublishedEvent());
}

std::string HideGuiPublishedEvent::getName()
{
    return "HideGuiPublishedEvent";
}
