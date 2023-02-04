#pragma once

#include "../Aggregator/PolygonPeekingEditorAggregator.h"
#include "../Core/EditorSupplier.h"
#include "GuiEditorEventConsumer.h"
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

    ~GuiEditor();

  protected:
    GuiEditor(Editor::SharedPtr pEditor);

  private:
    void showVertexList(Gui::Window &window);
    void showVertexInput(Gui::Window &window);

  private:
    float2 mNewPoint{0};
    Polygon::SharedPtr mpCurrentPolygon;
    Editor::SharedPtr mpEditor;
    EditorSupplier::SharedPtr mpCommandSupplier;
    PolygonPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    GuiEditorEventConsumer::SharedPtr mpEventConsumer;
};

} // namespace psdf
