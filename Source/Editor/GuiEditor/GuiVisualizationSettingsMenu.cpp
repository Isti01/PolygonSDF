#include "GuiVisualizationSettingsMenu.h"
#include "../../Rendering/PolygonRenderer/Impl/FullScreenPolygonRenderer.h"
#include "../../Rendering/PolygonRenderer/RendererProperties.h"
#include "../PublishedEvent/RendererPropertyPublishedEvent.h"

using namespace psdf;
using namespace Falcor;

const std::map<std::string, std::string> GuiVisualizationSettingsMenu::kPropertyTitles{
    {RendererProperties::kPolygonOutlineRendererEnabledProperty, "Enable polygon wireframe in the editor"},
    {RendererProperties::kPolygonOutlineColorProperty, "Polygon wireframe color"},
    {RendererProperties::kFullScreenPolygonRendererEnabledProperty, "Enable distance visualization in the editor"},
    {RendererProperties::kPositiveColorProperty, "Positive distance color"},
    {RendererProperties::kNegativeColorProperty, "Negative distance color"},
    {RendererProperties::kContourFrequencyProperty, "Distance contour frequency"},
    {RendererProperties::kContourIntensityProperty, "Distance contour intensity"},
    {RendererProperties::kDisplayShadowsProperty, "Display shadows"},
    {RendererProperties::kShadowsIntensityProperty, "Shadow locality"},
    {RendererProperties::kDisplayCloserToVertexProperty, "Darken segment regions"},
    {RendererProperties::kShouldDisplayContoursProperty, "Display distance contours"},
    {RendererProperties::kShouldColorBetweenContoursProperty, "Display coloring between contours"},
    {RendererProperties::kAlgorithmVisualizationCuttingPointCount, "Number of cutting points around output geometry"},
};

GuiVisualizationSettingsMenu::SharedPtr GuiVisualizationSettingsMenu::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiVisualizationSettingsMenu(std::move(pEditor)));
}

GuiVisualizationSettingsMenu::GuiVisualizationSettingsMenu(Editor::SharedPtr pEditor) : mpEditor(std::move(pEditor))
{
    resetProperties();
}

void GuiVisualizationSettingsMenu::renderGui(Gui::Window &window)
{
    Gui::Group group = window.group("Visualization Settings", true);
    if (!group)
    {
        return;
    }
    if (group.button("Reset to defaults"))
    {
        resetProperties();
        for (const auto &property : mProperties)
        {
            mpEditor->publishEvent(RendererPropertyPublishedEvent::create(property), this);
        }
    }

    for (auto &property : mProperties)
    {
        showPropertySetting(group, property);
    }
}

void GuiVisualizationSettingsMenu::resetProperties()
{
    mProperties = RendererProperties::kInitialProperties;
}

void GuiVisualizationSettingsMenu::showPropertySetting(Gui::Group &group, PolygonRendererProperty &property)
{
    const std::string &key = property.key;
    std::string title = kPropertyTitles.find(key) != kPropertyTitles.end() ? kPropertyTitles.at(property.key) : key;
    bool updated = false;
    if (float3 *pFloat3Value = std::get_if<float3>(&property.value))
    {
        if (property.key.find("Color") != std::string::npos)
        {
            updated = group.rgbColor(title.c_str(), *pFloat3Value);
        }
        else
        {
            updated = group.var(title.c_str(), *pFloat3Value);
        }
    }
    else if (float *pFloatValue = std::get_if<float>(&property.value))
    {
        updated = group.var(title.c_str(), *pFloatValue);
    }
    else if (size_t *pSizeValue = std::get_if<size_t>(&property.value))
    {
        updated = group.var(title.c_str(), *pSizeValue);
    }
    else if (bool *pBoolValue = std::get_if<bool>(&property.value))
    {
        updated = group.checkbox(title.c_str(), *pBoolValue);
    }
    if (updated)
    {
        mpEditor->publishEvent(RendererPropertyPublishedEvent::create(property), this);
    }
}
