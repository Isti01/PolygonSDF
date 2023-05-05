#include "TestConsumer.h"

using namespace psdf;

TestConsumer::SharedPtr TestConsumer::create()
{
    return SharedPtr(new TestConsumer());
}

void TestConsumer::accept(const EditorEvent::SharedPtr &pEvent)
{
    mAcceptedEvents.push_back(pEvent);
}

std::vector<EditorEvent::SharedPtr> TestConsumer::getAcceptedEvents() const
{
    return mAcceptedEvents;
}
