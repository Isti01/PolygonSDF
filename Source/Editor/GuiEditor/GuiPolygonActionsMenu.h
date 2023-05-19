#pragma once

#include "../Aggregator/StackPeekingEditorAggregator.h"
#include "../Core/Editor.h"
#include "GuiEditorMenu.h"

namespace psdf
{
using namespace Falcor;

class GuiPolygonActionsMenu : public GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiPolygonActionsMenu>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window) override;

  protected:
    GuiPolygonActionsMenu(Editor::SharedPtr pEditor);

  private:
    void showVertexList(size_t groupIndex, Gui::Group &window);
    void showGroupControls(size_t groupIndex, Gui::Group &window);

  private:
    float2 mNewPoint{0};
    float2 mGroupOffset{0};

    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    Polygon::SharedPtr mpCurrentPolygon = nullptr;
};

} // namespace psdf
