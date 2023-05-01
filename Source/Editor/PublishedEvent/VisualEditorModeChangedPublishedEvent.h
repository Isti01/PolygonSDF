#pragma once

#include "../Core/PublishedEvent.h"

namespace psdf
{

class VisualEditorModeChangedPublishedEvent : public PublishedEvent
{
  public:
    using SharedPtr = std::shared_ptr<VisualEditorModeChangedPublishedEvent>;

    static SharedPtr create(std::string stateName);

    std::string getName() override;
    std::string getStateName() const;

  protected:
    VisualEditorModeChangedPublishedEvent(std::string stateName);

  private:
    std::string mStateName;
};

} // namespace psdf
