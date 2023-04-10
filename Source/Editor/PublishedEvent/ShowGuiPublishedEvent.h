#pragma once

#include "../Core/PublishedEvent.h"

namespace psdf
{

class ShowGuiPublishedEvent : public PublishedEvent
{
  public:
    using SharedPtr = std::shared_ptr<ShowGuiPublishedEvent>;
    static SharedPtr create();

    std::string getName() override;
    ~ShowGuiPublishedEvent() override = default;

  protected:
    ShowGuiPublishedEvent() = default;
};

} // namespace psdf
