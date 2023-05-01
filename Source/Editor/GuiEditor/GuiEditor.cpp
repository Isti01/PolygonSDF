#include "GuiEditor.h"

using namespace psdf;

GuiEditor::SharedPtr GuiEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditor(std::move(pEditor)));
}

GuiEditor::GuiEditor(Editor::SharedPtr pEditor)
    : mpVisualizationsMenu(GuiVisualizationSettingsMenu::create(pEditor)),
      mpEditorActionsMenu(GuiEditorActionsMenu::create(pEditor)),
      mpPolygonActionsMenu(GuiPolygonActionsMenu::create(pEditor))
{
}

void GuiEditor::render(Gui::Window &window)
{
    mpVisualizationsMenu->renderGui(window);
    mpEditorActionsMenu->renderGui(window);
    mpPolygonActionsMenu->renderGui(window);
}
