#pragma once

#include "../Core/EditorConsumer.h"

namespace psdf
{

class GuiStateEditorConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<GuiStateEditorConsumer>;
    static SharedPtr create();

    void accept(const EditorEvent::SharedPtr &pEvent) override;

    bool isGuiEnabled() const;

  protected:
    GuiStateEditorConsumer() = default;

  private:
    bool mIsGuiEnabled = true;
};

} // namespace psdf
