#pragma once

#include "../Core/Editor.h"
namespace psdf
{
using namespace Falcor;

class GuiVisualizationSettingsMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiVisualizationSettingsMenu>;
    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window);

  protected:
    GuiVisualizationSettingsMenu(Editor::SharedPtr pEditor);

  private:
    bool mEnableDistanceVisualization = true;

    Editor::SharedPtr mpEditor;
};

} // namespace psdf
