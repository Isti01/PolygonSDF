#include "GuiEditor.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddNewGroupStackCommand.h"
#include "../Command/AddPointStackCommand.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"
#include "../Command/DeleteGroupStackCommand.h"
#include "../Command/DeletePointStackCommand.h"
#include "../Command/MergePolygonWithOffsetStackCommand.h"
#include "../Command/MoveGroupStackCommand.h"
#include "../Command/SetPolygonStackCommand.h"
#include "../Command/UpdatePointStackCommand.h"
#include "../Transformation/ClearHistoryEditorTransformation.h"
#include "../Transformation/UndoEditorTransformation.h"

#include <imgui.h>

using namespace psdf;

GuiEditor::SharedPtr GuiEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditor(std::move(pEditor)));
}

GuiEditor::GuiEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpStackSizeAggregator(StackSizeEditorAggregator::create()),
      mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create())
{
}

void GuiEditor::render(Gui::Window &window)
{
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    mpCurrentPolygon = pPeekResult->getEntry().polygon;
    Gui::Group group = window.group("GUI Polygon Editor", true);
    showControlButtons(group);
    ImGui::Spacing();

    if (!mpCurrentPolygon)
    {
        return;
    }
    for (size_t i = 0; i < mpCurrentPolygon->getPolygons().size(); i++)
    {
        WithImGuiId id(static_cast<int>(i));

        window.separator();
        ImGui::Spacing();
        showGroupControls(i, group);
        ImGui::Spacing();
        window.separator();
        ImGui::Spacing();
        showVertexList(i, group);
    }
}

static Polygon::SharedPtr loadPolygon()
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

void GuiEditor::showControlButtons(Gui::Group &window)
{
    WithImGuiId id("ControlButtons");

    size_t stackSize = mpStackSizeAggregator->getEditorStackSize(mpEditor)->getSize();
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

    if (window.button("Undo", true))
    {
        mpEditor->transform(UndoEditorTransformation::create());
    }

    if (window.button("Clear History"))
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
        if (auto polygon = loadPolygon())
        {
            mpEditor->addCommand(MergePolygonWithOffsetStackCommand::create(polygon, mPolygonOffset));
        }
    }
    if (mpCurrentPolygon && mpCurrentPolygon->getAlgorithmOutput() && window.button("Save Algorithm Output"))
    {
        std::filesystem::path path;
        Falcor::saveFileDialog({FileDialogFilter("json")}, path);
        if (path.empty() || !mpCurrentPolygon->getAlgorithmOutput()->saveJson(path.string()))
        {
            msgBox("Failed to save the algorithm output", MsgBoxType::Ok, Falcor::MsgBoxIcon::Info);
        }
    }
}

bool pointEntry(Gui::Group &window, float2 &point, size_t index)
{
    std::stringstream ss;
    ss << "[Vertex " << index << "]: \t";
    window.text(ss.str());
    ImGui::SameLine();
    return window.var("", point);
}

void GuiEditor::showVertexList(size_t groupIndex, Gui::Group &window)
{
    WithImGuiId id("VertexList");

    if (!mpCurrentPolygon)
    {
        window.text("There is no polygon in the editor");
        return;
    }

    auto polygon = mpCurrentPolygon->getPolygons()[groupIndex];
    std::vector<Point> points = polygon.getPoints();

    window.text("Vertex Editor");
    bool showDeleteButtons = points.size() > 3;
    for (size_t i = 0; i < points.size(); i++)
    {
        WithImGuiId vertexId(static_cast<int>(i));
        float2 point = points[i];
        if (pointEntry(window, point, i))
        {
            mpEditor->addCommand(UpdatePointStackCommand::create(groupIndex, i, point));
        }
        if (showDeleteButtons && window.button("Delete Vertex", true))
        {
            mpEditor->addCommand(DeletePointStackCommand::create(groupIndex, i));
        }
    }
}

void GuiEditor::showGroupControls(size_t groupIndex, Gui::Group &window)
{
    WithImGuiId id("GroupControlSection");
    window.text("Add New Vertex");
    window.var("", mNewPoint);
    if (window.button("Add Point", true))
    {
        mpEditor->addCommand(AddPointStackCommand::create(groupIndex, mNewPoint));
        mNewPoint = float2{0};
    }

    if (window.button("Delete Group"))
    {
        mpEditor->addCommand(DeleteGroupStackCommand::create(groupIndex));
    }

    {
        WithImGuiId id(2);
        window.var("", mGroupOffset);
        if (window.button("Offset Group", true))
        {
            auto firstPoint = mpCurrentPolygon->getPolygons()[groupIndex].getPoints().front();
            auto toPoint = firstPoint + Point(mGroupOffset);
            mpEditor->addCommand(MoveGroupStackCommand::create(groupIndex, firstPoint, toPoint));
        }
    }
}
