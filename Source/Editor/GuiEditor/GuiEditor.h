#pragma once

#include "../Aggregator/StackPeekingEditorAggregator.h"
#include "../Aggregator/StackSizeEditorAggregator.h"
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
    void showControlButtons(Gui::Group &window);
    void showVertexList(size_t groupIndex, Gui::Group &window);
    void showGroupControls(size_t groupIndex, Gui::Group &window);

  private:
    float2 mNewPoint{0};
    float2 mGroupOffset{0};
    float2 mPolygonOffset{0};
    Polygon::SharedPtr mpCurrentPolygon;
    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    StackSizeEditorAggregator::SharedPtr mpStackSizeAggregator;
};

} // namespace psdf
