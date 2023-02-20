#pragma once

#include "MouseInputHandler.h"

namespace psdf
{

class DragMouseInputHandler : public MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<DragMouseInputHandler>;

    static SharedPtr create();

    bool onMouseEvent(const MouseEvent &mouseEvent) override;
    void resetInputState() override;

    bool isDragging() const;
    bool isDragStarted() const;
    float2 getDragDelta() const;

  protected:
    DragMouseInputHandler() = default;

  private:
    bool mIsDragging{false};
    bool mIsDragStarted{false};

    float2 mLastMousePosition{0};
    float2 mDragDelta{0};
};

} // namespace psdf
