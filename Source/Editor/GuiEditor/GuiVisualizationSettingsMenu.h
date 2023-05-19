#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRendererProperty.h"
#include "../Core/Editor.h"
#include "GuiEditorMenu.h"

namespace psdf
{
using namespace Falcor;

class GuiVisualizationSettingsMenu : public GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiVisualizationSettingsMenu>;
    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window) override;

  protected:
    GuiVisualizationSettingsMenu(Editor::SharedPtr pEditor);

  private:
    void resetProperties();
    void showPropertySetting(Gui::Group &group, PolygonRendererProperty &property);
    static const std::map<std::string, std::string> kPropertyTitles;

    std::vector<PolygonRendererProperty> mProperties;
    Editor::SharedPtr mpEditor;
};

} // namespace psdf
