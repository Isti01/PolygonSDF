#pragma once

#include "../Aggregator/StackPeekingEditorAggregator.h"
#include "../Aggregator/StackSizeEditorAggregator.h"
#include "../Core/Editor.h"

namespace psdf
{

class GuiEditorActionsMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditorActionsMenu>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window);

  protected:
    GuiEditorActionsMenu(Editor::SharedPtr pEditor);

  private:
    static Polygon::SharedPtr loadPolygon();

  private:
    float2 mPolygonOffset{0};

    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    StackSizeEditorAggregator::SharedPtr mpStackSizeAggregator;
};

} // namespace psdf
