#pragma once

#include "../Core/EditorConsumer.h"
namespace psdf
{

class VisualEditorStateChangeEditorConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<VisualEditorStateChangeEditorConsumer>;

    static SharedPtr create();

    void accept(const EditorEvent::SharedPtr &pEvent) override;

    std::string getCurrentState() const;

  protected:
    VisualEditorStateChangeEditorConsumer() = default;

  private:
    std::string mCurrentState;
};

} // namespace psdf
