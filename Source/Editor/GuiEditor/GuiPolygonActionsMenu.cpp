#include "GuiPolygonActionsMenu.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddNewGroupStackCommand.h"
#include "../Command/AddPointStackCommand.h"
#include "../Command/DeleteGroupStackCommand.h"
#include "../Command/DeletePointStackCommand.h"
#include "../Command/MoveGroupStackCommand.h"
#include "../Command/UpdatePointStackCommand.h"

#include <imgui.h>

using namespace psdf;
using namespace Falcor;

GuiPolygonActionsMenu::SharedPtr GuiPolygonActionsMenu::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiPolygonActionsMenu(std::move(pEditor)));
}

GuiPolygonActionsMenu::GuiPolygonActionsMenu(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create())
{
}

void GuiPolygonActionsMenu::renderGui(Gui::Window &window)
{
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    mpCurrentPolygon = pPeekResult->getEntry().polygon;
    if (!mpCurrentPolygon)
    {
        return;
    }
    Gui::Group group = window.group("Polygon");
    if (!group)
    {
        return;
    }

    if (window.button("New Group"))
    {
        mpEditor->addCommand(AddNewGroupStackCommand::create(Polygon::kSquarePolygon->getPolygons()[0]));
    }
    size_t groupCount = mpCurrentPolygon->getPolygons().size();
    for (size_t i = 0; i < groupCount; i++)
    {
        WithImGuiId id(static_cast<int>(i));

        Gui::Group subPolygonGroup = group.group("Polygon Group [" + std::to_string(i) + "]", false);
        if (subPolygonGroup)
        {
            window.separator();
            ImGui::Spacing();
            showGroupControls(i, group);
            ImGui::Spacing();
            window.separator();
            ImGui::Spacing();
            showVertexList(i, group);
        }
        if (i != groupCount - 1)
        {
            ImGui::Spacing();
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

void GuiPolygonActionsMenu::showVertexList(size_t groupIndex, Gui::Group &window)
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
void GuiPolygonActionsMenu::showGroupControls(size_t groupIndex, Gui::Group &window)
{
    {
        WithImGuiId id("GroupControlSection");
        if (window.button("Delete Group"))
        {
            mpEditor->addCommand(DeleteGroupStackCommand::create(groupIndex));
        }

        window.text("Add New Vertex");
        window.var("", mNewPoint);
        if (window.button("Add Point", true))
        {
            mpEditor->addCommand(AddPointStackCommand::create(groupIndex, mNewPoint));
            mNewPoint = float2{0};
        }
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
