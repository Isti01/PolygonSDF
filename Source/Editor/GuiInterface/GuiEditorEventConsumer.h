#pragma once

#include "../Core/Editor.h"
#include <memory>

namespace psdf
{

class GuiEditorEventConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditorEventConsumer>;

    static SharedPtr create();

    void accept(const EditorEvent::SharedPtr &pEvent) override;

  protected:
    GuiEditorEventConsumer() = default;
};

}; // namespace psdf
