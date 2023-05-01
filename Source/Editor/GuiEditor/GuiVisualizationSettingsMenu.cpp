#include "GuiVisualizationSettingsMenu.h"
#include "../../Rendering/PolygonRenderer/Impl/FullScreenPolygonRenderer.h"
#include "../PublishedEvent/RendererPropertyPublishedEvent.h"

using namespace psdf;
using namespace Falcor;

GuiVisualizationSettingsMenu::SharedPtr GuiVisualizationSettingsMenu::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiVisualizationSettingsMenu(std::move(pEditor)));
}

GuiVisualizationSettingsMenu::GuiVisualizationSettingsMenu(Editor::SharedPtr pEditor) : mpEditor(std::move(pEditor))
{
}

void GuiVisualizationSettingsMenu::renderGui(Gui::Window &window)
{
    Gui::Group group = window.group("Visualization Settings");
    if (!group)
    {
        return;
    }

    if (group.checkbox("Enable Distance Visualization In The Editor", mEnableDistanceVisualization))
    {
        PolygonRendererProperty property{FullScreenPolygonRenderer::kFullScreenPolygonRendererEnabledProperty,
                                         mEnableDistanceVisualization};
        mpEditor->publishEvent(RendererPropertyPublishedEvent::create(property), this);
    }
}
