#include "VisualEditorModeChangedPublishedEvent.h"

#include <sstream>

using namespace psdf;

VisualEditorModeChangedPublishedEvent::SharedPtr VisualEditorModeChangedPublishedEvent::create(std::string stateName)
{
    return SharedPtr(new VisualEditorModeChangedPublishedEvent(std::move(stateName)));
}

VisualEditorModeChangedPublishedEvent::VisualEditorModeChangedPublishedEvent(std::string stateName)
    : mStateName(std::move(stateName))
{
}

std::string VisualEditorModeChangedPublishedEvent::getName()
{
    std::stringstream ss;
    ss << "VisualEditorModeChangedPublishedEvent(" << mStateName << ')';
    return ss.str();
}

std::string VisualEditorModeChangedPublishedEvent::getStateName() const
{
    return mStateName;
}
