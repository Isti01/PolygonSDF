#include "RendererPropertyPublishedEvent.h"

using namespace psdf;

RendererPropertyPublishedEvent::SharedPtr RendererPropertyPublishedEvent::create(ShapeRendererProperty property)
{
    return SharedPtr(new RendererPropertyPublishedEvent(std::move(property)));
}

RendererPropertyPublishedEvent::RendererPropertyPublishedEvent(ShapeRendererProperty property)
    : mProperty(std::move(property))
{
}

ShapeRendererProperty RendererPropertyPublishedEvent::getProperty() const
{
    return mProperty;
}

std::string RendererPropertyPublishedEvent::getName()
{
    std::stringstream ss;
    ss << "RendererPropertyPublishedEvent(" << mProperty.key << ')';
    return ss.str();
}
