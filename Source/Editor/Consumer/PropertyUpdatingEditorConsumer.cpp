#include "PropertyUpdatingEditorConsumer.h"
#include "../PublishedEvent/RendererPropertyPublishedEvent.h"

using namespace psdf;

PropertyUpdatingEditorConsumer::SharedPtr PropertyUpdatingEditorConsumer::create(ShapeRenderer::SharedPtr pRenderer)
{
    return SharedPtr(new PropertyUpdatingEditorConsumer(std::move(pRenderer)));
}

PropertyUpdatingEditorConsumer::PropertyUpdatingEditorConsumer(ShapeRenderer::SharedPtr pRenderer)
    : mpRenderer(std::move(pRenderer))
{
}

void PropertyUpdatingEditorConsumer::accept(const EditorEvent::SharedPtr &pEvent)
{
    if (auto pPublishedEvent = std::dynamic_pointer_cast<EditorPublishedEvent>(pEvent))
    {
        if (auto pPropEvent = std::dynamic_pointer_cast<RendererPropertyPublishedEvent>(pPublishedEvent->getEvent()))
        {
            mpRenderer->setProperty(pPropEvent->getProperty());
        }
    }
}
