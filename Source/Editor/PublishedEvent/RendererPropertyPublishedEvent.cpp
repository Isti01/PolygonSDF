#include "RendererPropertyPublishedEvent.h"

using namespace psdf;

RendererPropertyPublishedEvent::SharedPtr RendererPropertyPublishedEvent::create(PolygonRendererProperty property)
{
    return SharedPtr(new RendererPropertyPublishedEvent(std::move(property)));
}

RendererPropertyPublishedEvent::RendererPropertyPublishedEvent(PolygonRendererProperty property)
    : mProperty(std::move(property))
{
}

PolygonRendererProperty RendererPropertyPublishedEvent::getProperty() const
{
    return mProperty;
}

std::string RendererPropertyPublishedEvent::getName()
{
    std::stringstream ss;
    ss << "RendererPropertyPublishedEvent(" << mProperty.key << ')';
    return ss.str();
}
