#pragma once

#include "../Aggregator/PolygonPeekingEditorAggregator.h"
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

    void render(Gui *pGui);

  protected:
    GuiEditor(Editor::SharedPtr pEditor);

  private:
    void showControlButtons(Gui::Window& window);
    void showVertexList(Gui::Window &window);
    void showVertexInput(Gui::Window &window);

  private:
    float2 mNewPoint{0};
    Polygon::SharedPtr mpCurrentPolygon;
    Editor::SharedPtr mpEditor;
    PolygonPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    StackSizeEditorAggregator::SharedPtr mpStackSizeAggregator;
};

} // namespace psdf
