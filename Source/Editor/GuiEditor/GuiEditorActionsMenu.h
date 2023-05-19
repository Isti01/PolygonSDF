#pragma once

#include "../Aggregator/StackPeekingEditorAggregator.h"
#include "../Aggregator/StackSizeEditorAggregator.h"
#include "../Core/Editor.h"
#include "GuiEditorMenu.h"

namespace psdf
{

class GuiEditorActionsMenu : public GuiEditorMenu
{
  public:
    using SharedPtr = std::shared_ptr<GuiEditorActionsMenu>;

    static SharedPtr create(Editor::SharedPtr pEditor);

    void renderGui(Gui::Window &window) override;

  protected:
    GuiEditorActionsMenu(Editor::SharedPtr pEditor);

  private:
    static Shape::SharedPtr loadShape();

  private:
    SdfPlaneAlgorithmExecutionDesc mExecutionDesc = kDefaultSdfPlaneAlgorithmExecutionDesc;
    float2 pShapeOffset{0};

    Editor::SharedPtr mpEditor;
    StackPeekingEditorAggregator::SharedPtr mpPolygonPeekingAggregator;
    StackSizeEditorAggregator::SharedPtr mpStackSizeAggregator;
};

} // namespace psdf
