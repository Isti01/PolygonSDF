#include "GuiEditor.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddPointStackCommand.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"
#include "../Command/DeletePointStackCommand.h"
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

    for (size_t i = 0; i < mpCurrentPolygon->getPolygons().size(); i++)
    {
        WithImGuiId id(static_cast<int>(i));

        window.separator();
        ImGui::Spacing();
        showVertexInput(i, group);
        ImGui::Spacing();
        window.separator();
        ImGui::Spacing();
        showVertexList(i, group);
    }
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
        mpEditor->addCommand(SetPolygonStackCommand::create(Polygon::kExamplePolygon));
    }

    if (window.button("Undo", true))
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

void GuiEditor::showVertexInput(size_t groupIndex, Gui::Group &window)
{
    if (!mpCurrentPolygon)
    {
        return;
    }

    WithImGuiId id("VertexInputSection");
    window.text("Add New Vertex");
    window.var("", mNewPoint);
    if (window.button("Add Point", true))
    {
        mpEditor->addCommand(AddPointStackCommand::create(groupIndex, mNewPoint));
        mNewPoint = float2{0};
    }
}
