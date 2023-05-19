#include "GuiEditor.h"
#include "EditorGuideMenu.h"
#include "EventMenu.h"
#include "GuiEditorActionsMenu.h"
#include "GuiShapeActionsMenu.h"
#include "GuiVisualizationSettingsMenu.h"

using namespace psdf;

GuiEditor::SharedPtr GuiEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditor(std::move(pEditor)));
}

GuiEditor::GuiEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpStateChangeConsumer(VisualEditorStateChangeEditorConsumer::create()),
      menus({GuiVisualizationSettingsMenu::create(mpEditor), GuiEditorActionsMenu::create(mpEditor),
             GuiShapeActionsMenu::create(mpEditor), EventMenu::create(mpEditor), EditorGuideMenu::create()})
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
    for (const auto &menu : menus)
    {
        menu->renderGui(window);
    }
}
