#pragma once

#include "../Aggregator/StackPeekingEditorAggregator.h"
#include "../Core/Editor.h"
#include "GuiEditorMenu.h"

namespace psdf
{
using namespace Falcor;

class GuiShapeActionsMenu : public GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiShapeActionsMenu>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window) override;

  protected:
    GuiShapeActionsMenu(Editor::SharedPtr pEditor);

  private:
    void showVertexList(size_t outlineIndex, Gui::Group &window);
    void showGroupControls(size_t outlineIndex, Gui::Group &window);

  private:
    float2 mNewPoint{0};
    float2 mOutlineOffset{0};

    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    Shape::SharedPtr mpCurrentShape = nullptr;
};

} // namespace psdf
