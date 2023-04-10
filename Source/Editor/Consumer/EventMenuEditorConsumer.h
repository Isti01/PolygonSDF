#pragma once

#include "../Core/EditorConsumer.h"
#include "../Event/Menu/EventMenuGui.h"

namespace psdf
{

class EventMenuEditorConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<EventMenuEditorConsumer>;
    static SharedPtr create(EventMenuGui::SharedPtr pEventMenu);

  protected:
    EventMenuEditorConsumer(EventMenuGui::SharedPtr pEventMenu);

  public:
    void accept(const EditorEvent::SharedPtr &pEvent) override;

  private:
    EventMenuGui::SharedPtr mpEventMenu;
};

} // namespace psdf
