#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class MouseInputHandler
{
  public:
    using SharedPtr = std::shared_ptr<MouseInputHandler>;

    virtual bool onMouseEvent(const MouseEvent &mouseEvent) = 0;
    virtual void resetInputState() = 0;

    virtual ~MouseInputHandler() = default;
};

} // namespace psdf
