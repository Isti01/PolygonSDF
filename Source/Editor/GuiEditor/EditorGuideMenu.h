#pragma once

#include "GuiEditorMenu.h"

namespace psdf
{
using namespace Falcor;

class EditorGuideMenu : public GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<EditorGuideMenu>;

    static SharedPtr create();

    void renderGui(Gui::Window &window) override;

  protected:
    EditorGuideMenu() = default;
};

} // namespace psdf
