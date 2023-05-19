#include "GuiEditorActionsMenu.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"
#include "../Command/MergeShapeWithOffsetStackCommand.h"
#include "../Command/SetShapeStackCommand.h"
#include "../Transformation/ClearHistoryEditorTransformation.h"
#include "../Transformation/UndoEditorTransformation.h"

#include <imgui.h>

using namespace psdf;
using namespace Falcor;

GuiEditorActionsMenu::SharedPtr GuiEditorActionsMenu::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditorActionsMenu(std::move(pEditor)));
}

GuiEditorActionsMenu::GuiEditorActionsMenu(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpStackSizeAggregator(StackSizeEditorAggregator::create()),
      mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create())
{
}

void GuiEditorActionsMenu::renderGui(Gui::Window &window)
{
    Gui::Group group = window.group("Editor Actions", true);
    if (!group)
    {
        return;
    }

    WithImGuiId id("ControlButtons");

    size_t stackSize = mpStackSizeAggregator->getEditorStackSize(mpEditor)->getSize();
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    auto pShape = pPeekResult->getEntry().pShape;
    std::stringstream ss;
    ss << "Commands in the editor stack: " << stackSize;
    window.text(ss.str());
    if (window.button("New Shape"))
    {
        if (auto shape = loadShape())
        {
            mpEditor->addCommand(SetShapeStackCommand::create(shape));
        }
    }
    if (window.button("Set to starter shape", true))
    {
        mpEditor->addCommand(SetShapeStackCommand::create(Shape::kStarterShape));
    }

    if (window.button("Undo"))
    {
        mpEditor->transform(UndoEditorTransformation::create());
    }

    if (window.button("Clear History", true))
    {
        mpEditor->transform(ClearHistoryEditorTransformation::create());
    }

    if (pShape)
    {
        ImGui::Spacing();
        window.var("Initial region bound scale: ", mExecutionDesc.initialBoundScale, 0.0);
        window.var("Vertex region subdivision count: ", mExecutionDesc.vertexRegionSubdivision, size_t(3));
        if (window.button("Run Plane Slicing Algorithm"))
        {
            mpEditor->addCommand(CalculateSdfPlaneAlgorithmCommand::create(mExecutionDesc));
            if (!mpPolygonPeekingAggregator->peekEditor(mpEditor)->getEntry().pShape->getAlgorithmOutput())
            {
                msgBox("Failed to run the algorthm on the current shape\nTip: Check for intersecting segments!",
                       MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
            }
        }
    }

    ImGui::Spacing();
    window.var("Offset: ", pShapeOffset);
    if (window.button("Add Shape with offset", true))
    {
        if (auto shape = GuiEditorActionsMenu::loadShape())
        {
            mpEditor->addCommand(MergeShapeWithOffsetStackCommand::create(shape, pShapeOffset));
        }
    }
    if (pShape && window.button("Save shape"))
    {
        std::filesystem::path path;
        Falcor::saveFileDialog({FileDialogFilter("json")}, path);
        if (path.empty() || !pShape->saveJson(path.string()))
        {
            msgBox("Failed to save the shape", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
    }
    if (pShape->getAlgorithmOutput() && window.button("Save Algorithm Output", true))
    {
        std::filesystem::path path;
        Falcor::saveFileDialog({FileDialogFilter("json")}, path);
        if (path.empty() || !pShape->getAlgorithmOutput()->saveJson(path.string()))
        {
            msgBox("Failed to save the algorithm output", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
    }
}

Shape::SharedPtr GuiEditorActionsMenu::loadShape()
{
    std::filesystem::path path;
    openFileDialog({FileDialogFilter("json")}, path);
    if (!path.empty())
    {
        auto shape = Shape::fromJson(path.string());
        if (!shape)
        {
            msgBox("Failed to load the shape", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
        else
        {
            return shape;
        }
    }
    return nullptr;
}
