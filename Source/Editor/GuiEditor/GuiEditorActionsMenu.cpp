#include "GuiEditorActionsMenu.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"
#include "../Command/MergePolygonWithOffsetStackCommand.h"
#include "../Command/SetPolygonStackCommand.h"
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
    auto pPolygon = pPeekResult->getEntry().polygon;
    std::stringstream ss;
    ss << "Commands in the editor stack: " << stackSize;
    window.text(ss.str());
    if (window.button("New Polygon"))
    {
        if (auto polygon = loadPolygon())
        {
            mpEditor->addCommand(SetPolygonStackCommand::create(polygon));
        }
    }
    if (window.button("New Placeholder Polygon", true))
    {
        mpEditor->addCommand(SetPolygonStackCommand::create(Polygon::kExamplePolygon));
    }

    if (window.button("Undo"))
    {
        mpEditor->transform(UndoEditorTransformation::create());
    }

    if (window.button("Clear History", true))
    {
        mpEditor->transform(ClearHistoryEditorTransformation::create());
    }

    if (pPolygon)
    {
        ImGui::Spacing();
        window.var("Initial region bound scale: ", mExecutionDesc.initialBoundScale, 0.0);
        window.var("Point region subdivision count: ", mExecutionDesc.pointRegionSubdivision, size_t(3));
        if (window.button("Run Plane Slicing Algorithm"))
        {
            mpEditor->addCommand(CalculateSdfPlaneAlgorithmCommand::create(mExecutionDesc));
            if (!mpPolygonPeekingAggregator->peekEditor(mpEditor)->getEntry().polygon->getAlgorithmOutput())
            {
                msgBox("Failed to run the algorthm on the current polygon\nTip: Check for intersecting segments!",
                       MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
            }
        }
    }

    ImGui::Spacing();
    window.var("Offset: ", mPolygonOffset);
    if (window.button("Add Polygon with offset", true))
    {
        if (auto polygon = GuiEditorActionsMenu::loadPolygon())
        {
            mpEditor->addCommand(MergePolygonWithOffsetStackCommand::create(polygon, mPolygonOffset));
        }
    }
    if (pPolygon && window.button("Save polygon"))
    {
        std::filesystem::path path;
        Falcor::saveFileDialog({FileDialogFilter("json")}, path);
        if (path.empty() || !pPolygon->saveJson(path.string()))
        {
            msgBox("Failed to save the polygon", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
    }
    if (pPolygon->getAlgorithmOutput() && window.button("Save Algorithm Output", true))
    {
        std::filesystem::path path;
        Falcor::saveFileDialog({FileDialogFilter("json")}, path);
        if (path.empty() || !pPolygon->getAlgorithmOutput()->saveJson(path.string()))
        {
            msgBox("Failed to save the algorithm output", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
    }
}

Polygon::SharedPtr GuiEditorActionsMenu::loadPolygon()
{
    std::filesystem::path path;
    openFileDialog({FileDialogFilter("json")}, path);
    if (!path.empty())
    {
        auto polygon = Polygon::fromJson(path.string());
        if (!polygon)
        {
            msgBox("Failed to load the polygon", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
        else
        {
            return polygon;
        }
    }
    return nullptr;
}
