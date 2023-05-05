#pragma once

#include "../../Source/Editor/Core/EditorConsumer.h"

#include <vector>

namespace psdf
{

class TestConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<TestConsumer>;

    static SharedPtr create();

    void accept(const EditorEvent::SharedPtr &pEvent) override;

    std::vector<EditorEvent::SharedPtr> getAcceptedEvents() const;

  protected:
    TestConsumer() = default;

  private:
    std::vector<EditorEvent::SharedPtr> mAcceptedEvents;
};

} // namespace psdf
