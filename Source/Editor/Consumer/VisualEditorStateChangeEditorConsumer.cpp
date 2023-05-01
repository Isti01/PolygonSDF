#include "VisualEditorStateChangeEditorConsumer.h"
#include "../Core/PublishedEvent.h"
#include "../PublishedEvent/VisualEditorModeChangedPublishedEvent.h"

using namespace psdf;

VisualEditorStateChangeEditorConsumer::SharedPtr VisualEditorStateChangeEditorConsumer::create()
{
    return SharedPtr(new VisualEditorStateChangeEditorConsumer());
}

void VisualEditorStateChangeEditorConsumer::accept(const EditorEvent::SharedPtr &pEvent)
{
    if (auto pPubEv = std::dynamic_pointer_cast<EditorPublishedEvent>(pEvent))
    {
        if (auto pStateEv = std::dynamic_pointer_cast<VisualEditorModeChangedPublishedEvent>(pPubEv->getEvent()))
        {
            mCurrentState = pStateEv->getStateName();
        }
    }
}

std::string VisualEditorStateChangeEditorConsumer::getCurrentState() const
{
    return mCurrentState;
}
