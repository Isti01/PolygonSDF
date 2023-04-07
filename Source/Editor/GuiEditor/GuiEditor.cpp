#include "GuiEditor.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddPointStackCommand.h"
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

void GuiEditor::render(Gui::Window& window)
{
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    mpCurrentPolygon = pPeekResult->getEntry().polygon;
    Gui::Group group = window.group("GUI Polygon Editor", true);
    showControlButtons(group);
    ImGui::Spacing();
    window.separator();
    ImGui::Spacing();
    showVertexInput(group);
    ImGui::Spacing();
    window.separator();
    ImGui::Spacing();
    showVertexList(group);
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
}

bool pointEntry(Gui::Group &window, float2 &point, size_t index)
{
    std::stringstream ss;
    ss << "[Vertex " << index << "]: \t";
    window.text(ss.str());
    ImGui::SameLine();
    return window.var("", point);
}

void GuiEditor::showVertexList(Gui::Group &window)
{
    WithImGuiId id("VertexList");

    if (!mpCurrentPolygon)
    {
        window.text("There is no polygon in the editor");
        return;
    }

    bool showDeleteButtons = mpCurrentPolygon->getPoints().size() > 3;

    window.text("Vertex Editor");
    std::vector<Point> points = mpCurrentPolygon->getPoints();
    for (size_t i = 0; i < points.size(); i++)
    {
        WithImGuiId vertexId(static_cast<int>(i));
        float2 point = points[i];
        if (pointEntry(window, point, i))
        {
            mpEditor->addCommand(UpdatePointStackCommand::create(i, point));
        }
        if (showDeleteButtons && window.button("Delete Vertex", true))
        {
            mpEditor->addCommand(DeletePointStackCommand::create(i));
        }
    }
}

void GuiEditor::showVertexInput(Gui::Group &window)
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
        mpEditor->addCommand(AddPointStackCommand::create(mNewPoint));
        mNewPoint = float2{0};
    }
}
