#pragma once

#include "../Aggregator/StackPeekingEditorAggregator.h"
#include "../Aggregator/StackSizeEditorAggregator.h"
#include "EventMenu.h"
#include "GuiEditorActionsMenu.h"
#include "GuiPolygonActionsMenu.h"
#include "GuiVisualizationSettingsMenu.h"
#include <Falcor.h>
#include <memory>

namespace psdf
{
using namespace Falcor;

class GuiEditor
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditor>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void render(Gui::Window &window);

  protected:
    GuiEditor(Editor::SharedPtr pEditor);

  private:
    GuiVisualizationSettingsMenu::SharedPtr mpVisualizationsMenu;
    GuiEditorActionsMenu::SharedPtr mpEditorActionsMenu;
    GuiPolygonActionsMenu::SharedPtr mpPolygonActionsMenu;
    EventMenu::SharedPtr mpEventMenu;
};

} // namespace psdf
