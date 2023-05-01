#pragma once

#include "../Core/Editor.h"
#include "Falcor.h"

namespace psdf
{
using namespace Falcor;

class EventMenuGui
{
  public:
    using SharedPtr = std::shared_ptr<EventMenuGui>;
    static SharedPtr create();

    void renderGui(Gui::Window &window);
    void addNewEvent(EditorEvent::SharedPtr pEvent);

  protected:
    EventMenuGui() = default;

  private:
    void renderCumulatedEvents(Gui::Group &group) const;
    std::string EventMenuGui::getCumulatedText(size_t repeats, const std::string &text) const;

  private:
    std::vector<EditorEvent::SharedPtr> mEvents;
};

} // namespace psdf
