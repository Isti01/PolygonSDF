#include "GuiEditor.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddPointStackCommand.h"
#include "../Command/DeletePointStackCommand.h"
#include "../Command/UpdatePointStackCommand.h"

#include <imgui.h>

using namespace psdf;

GuiEditor::SharedPtr GuiEditor::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiEditor(std::move(pEditor)));
}

GuiEditor::GuiEditor(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpCommandSupplier(EditorSupplier::create(mpEditor)),
      mpEventConsumer(GuiEditorEventConsumer::create()),
      mpPolygonPeekingAggregator(PolygonPeekingEditorAggregator::create())
{
    mpEditor->addConsumer(std::static_pointer_cast<EditorConsumer>(mpEventConsumer));
}

void GuiEditor::render(Gui *pGui)
{
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    mpCurrentPolygon = pPeekResult->getPolygon();
    Gui::Window window(pGui, "GUI Polygon Editor");

    showVertexList(window);
    window.separator();
    showVertexInput(window);
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

    std::vector<Point> points = mpCurrentPolygon->getPoints();
    for (size_t i = 0; i < points.size(); i++)
    {
        WithImGuiId vertexId(static_cast<int>(i));
        auto point = points[i].getCoordinates();
        if (pointEntry(window, point, i))
        {
            mpCommandSupplier->dispatchCommand(UpdatePointStackCommand::create(i, point));
        }
        if (window.button("Delete Vertex", true))
        {
            mpCommandSupplier->dispatchCommand(DeletePointStackCommand::create(i));
        }
    }
}

void GuiEditor::showVertexInput(Gui::Window &window)
{
    WithImGuiId id("VertexInputSection");

    window.var("", mNewPoint);
    if (window.button("Add Point", true))
    {
        mpCommandSupplier->dispatchCommand(AddPointStackCommand::create(mNewPoint));
        mNewPoint = float2{0};
    }
}

GuiEditor::~GuiEditor()
{
    mpEditor->removeConsumer(std::static_pointer_cast<EditorConsumer>(mpEventConsumer));
}
