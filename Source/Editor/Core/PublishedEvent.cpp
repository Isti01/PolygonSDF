#include <sstream>

#include "PublishedEvent.h"

using namespace psdf;

EditorPublishedEvent::SharedPtr EditorPublishedEvent::create(PublishedEvent::SharedPtr pPublishedEvent,
                                                             const void *pPublisher)
{
    return SharedPtr(new EditorPublishedEvent(std::move(pPublishedEvent), pPublisher));
}

EditorPublishedEvent::EditorPublishedEvent(PublishedEvent::SharedPtr pPublishedEvent, const void *pPublisher)
    : mpPublishedEvent(std::move(pPublishedEvent)), mpPublisher(pPublisher)
{
}

PublishedEvent::SharedPtr EditorPublishedEvent::getEvent() const
{
    return mpPublishedEvent;
}

const void *EditorPublishedEvent::getPublisher() const
{
    return mpPublisher;
}

std::string EditorPublishedEvent::getName() const
{
    std::stringstream ss;
    ss << "EditorPublishedEvent(" << mpPublishedEvent->getName() << ')';
    return ss.str();
}
