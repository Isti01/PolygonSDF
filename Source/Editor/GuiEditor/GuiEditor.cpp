#include "GuiEditor.h"

using namespace psdf;

GuiEditor::SharedPtr GuiEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditor(std::move(pEditor)));
}

GuiEditor::GuiEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpStateChangeConsumer(VisualEditorStateChangeEditorConsumer::create()),
      mpVisualizationsMenu(GuiVisualizationSettingsMenu::create(mpEditor)),
      mpEditorActionsMenu(GuiEditorActionsMenu::create(mpEditor)),
      mpPolygonActionsMenu(GuiPolygonActionsMenu::create(mpEditor)), mpEventMenu(EventMenu::create(mpEditor))
{
    mpEditor->addConsumer(mpStateChangeConsumer);
}

GuiEditor::~GuiEditor()
{
    mpEditor->removeConsumer(mpStateChangeConsumer);
}

void GuiEditor::render(Gui::Window &window)
{
    window.text("Visual editor Mode:");
    window.text(mpStateChangeConsumer->getCurrentState(), true);
    mpVisualizationsMenu->renderGui(window);
    mpEditorActionsMenu->renderGui(window);
    mpPolygonActionsMenu->renderGui(window);
    mpEventMenu->renderGui(window);
}
