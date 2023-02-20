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

void GuiEditor::render(Gui *pGui)
{
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    mpCurrentPolygon = pPeekResult->getEntry().polygon;
    Gui::Window window(pGui, "GUI Polygon Editor");

    showControlButtons(window);
    ImGui::Spacing();
    window.separator();
    ImGui::Spacing();
    showVertexList(window);
    ImGui::Spacing();
    window.separator();
    ImGui::Spacing();
    showVertexInput(window);
}

void GuiEditor::showControlButtons(Gui::Window &window)
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

bool pointEntry(Gui::Window &window, float2 &point, size_t index)
{
    std::stringstream ss;
    ss << "[Vertex " << index << "]: \t";
    window.text(ss.str());
    ImGui::SameLine();
    return window.var("", point);
}

void GuiEditor::showVertexList(Gui::Window &window)
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
        auto point = points[i].getCoordinates();
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

void GuiEditor::showVertexInput(Gui::Window &window)
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
