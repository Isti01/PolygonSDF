#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../Core/PublishedEvent.h"

namespace psdf
{

class RendererPropertyPublishedEvent : public PublishedEvent
{
  public:
    using SharedPtr = std::shared_ptr<RendererPropertyPublishedEvent>;
    static SharedPtr create(PolygonRendererProperty property);

    std::string getName() override;
    PolygonRendererProperty getProperty() const;
    ~RendererPropertyPublishedEvent() override = default;

  protected:
    RendererPropertyPublishedEvent(PolygonRendererProperty property);

  private:
    PolygonRendererProperty mProperty;
};

} // namespace psdf
