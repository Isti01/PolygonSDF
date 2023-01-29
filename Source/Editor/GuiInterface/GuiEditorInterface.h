#pragma once

#include "../Aggregator/PolygonPeekingEditorAggregator.h"
#include "../Core/EditorSupplier.h"
#include "GuiEditorEventConsumer.h"
#include <Falcor.h>
#include <memory>

namespace psdf
{
using namespace Falcor;

class GuiEditorInterface
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditorInterface>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void render(Gui *pGui)
    {
        Gui::Window window(pGui, "GUI Polygon Editor");
    }

    ~GuiEditorInterface();

  protected:
    GuiEditorInterface(Editor::SharedPtr pEditor);


  private:
    Editor::SharedPtr mpEditor;
    EditorSupplier::SharedPtr mpCommandSupplier;
    PolygonPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    GuiEditorEventConsumer::SharedPtr mpEventConsumer;
};

} // namespace psdf
