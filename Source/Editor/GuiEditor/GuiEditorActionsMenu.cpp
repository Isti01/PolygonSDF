#include "GuiEditorActionsMenu.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddNewGroupStackCommand.h"
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

    if (window.button("New Group", true))
    {
        mpEditor->addCommand(AddNewGroupStackCommand::create(Polygon::kSquarePolygon->getPolygons()[0]));
    }

    if (window.button("Undo"))
    {
        mpEditor->transform(UndoEditorTransformation::create());
    }

    if (window.button("Clear History", true))
    {
        mpEditor->transform(ClearHistoryEditorTransformation::create());
    }

    if (window.button("Run Plane Slicing Algorithm", true))
    {
        mpEditor->addCommand(CalculateSdfPlaneAlgorithmCommand::create());
    }

    ImGui::Spacing();
    window.var("", mPolygonOffset);
    if (window.button("Add Polygon with offset", true))
    {
        if (auto polygon = GuiEditorActionsMenu::loadPolygon())
        {
            mpEditor->addCommand(MergePolygonWithOffsetStackCommand::create(polygon, mPolygonOffset));
        }
    }
    if (pPolygon->getAlgorithmOutput() && window.button("Save Algorithm Output"))
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
