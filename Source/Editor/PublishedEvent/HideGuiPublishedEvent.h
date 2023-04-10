#pragma once

#include "../Core/PublishedEvent.h"

namespace psdf
{

class HideGuiPublishedEvent : public PublishedEvent
{
  public:
    using SharedPtr = std::shared_ptr<HideGuiPublishedEvent>;
    static SharedPtr create();

    std::string getName() override;
    ~HideGuiPublishedEvent() override = default;

  protected:
    HideGuiPublishedEvent() = default;
};

} // namespace psdf
