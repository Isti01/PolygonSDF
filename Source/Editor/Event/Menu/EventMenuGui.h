#pragma once

#include "../../Core/Editor.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class EventMenuGui
{
  public:
    using SharedPtr = std::shared_ptr<EventMenuGui>;
    static SharedPtr create();

    void renderGui(Gui *pGui);
    void addNewEvent(EditorEvent::SharedPtr pEvent);

  protected:
    EventMenuGui() = default;

  private:
    std::vector<EditorEvent::SharedPtr> mEvents;
};

} // namespace psdf
