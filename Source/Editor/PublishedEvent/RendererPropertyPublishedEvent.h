#pragma once

#include "../../Rendering/ShapeRenderer/ShapeRenderer.h"
#include "../Core/PublishedEvent.h"

namespace psdf
{

class RendererPropertyPublishedEvent : public PublishedEvent
{
  public:
    using SharedPtr = std::shared_ptr<RendererPropertyPublishedEvent>;
    static SharedPtr create(ShapeRendererProperty property);

    std::string getName() override;
    ShapeRendererProperty getProperty() const;
    ~RendererPropertyPublishedEvent() override = default;

  protected:
    RendererPropertyPublishedEvent(ShapeRendererProperty property);

  private:
    ShapeRendererProperty mProperty;
};

} // namespace psdf
