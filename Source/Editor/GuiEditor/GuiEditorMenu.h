#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditorMenu>;

    virtual void renderGui(Gui::Window &window) = 0;
};

} // namespace psdf
