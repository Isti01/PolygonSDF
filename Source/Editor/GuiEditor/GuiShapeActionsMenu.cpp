#include "GuiShapeActionsMenu.h"
#include "../../Util/WithImGuiId.h"
#include "../Command/AddNewOutlineStackCommand.h"
#include "../Command/AddVertexStackCommand.h"
#include "../Command/DeleteOutlineStackCommand.h"
#include "../Command/DeleteVertexStackCommand.h"
#include "../Command/MoveOutlineStackCommand.h"
#include "../Command/UpdateVertexStackCommand.h"

#include <imgui.h>

using namespace psdf;
using namespace Falcor;

GuiShapeActionsMenu::SharedPtr GuiShapeActionsMenu::create(Editor::SharedPtr pEditor)
{
    return SharedPtr(new GuiShapeActionsMenu(std::move(pEditor)));
}

GuiShapeActionsMenu::GuiShapeActionsMenu(Editor::SharedPtr pEditor)
    : mpEditor(std::move(pEditor)), mpPolygonPeekingAggregator(StackPeekingEditorAggregator::create())
{
}

void GuiShapeActionsMenu::renderGui(Gui::Window &window)
{
    auto pPeekResult = mpPolygonPeekingAggregator->peekEditor(mpEditor);
    FALCOR_ASSERT(pPeekResult);
    mpCurrentShape = pPeekResult->getEntry().pShape;
    if (!mpCurrentShape)
    {
        return;
    }
    Gui::Group group = window.group("Shape");
    if (!group)
    {
        return;
    }

    if (window.button("New Outline"))
    {
        mpEditor->addCommand(AddNewOutlineStackCommand::create(Shape::kSquareShape->getOutlines()[0]));
    }
    size_t outlineCount = mpCurrentShape->getOutlines().size();
    for (size_t i = 0; i < outlineCount; i++)
    {
        WithImGuiId id(static_cast<int>(i));

        Gui::Group subPolygonGroup = group.group("Shape Outline [" + std::to_string(i) + "]", false);
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
        if (i != outlineCount - 1)
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

void GuiShapeActionsMenu::showVertexList(size_t outlineIndex, Gui::Group &window)
{
    WithImGuiId id("VertexList");

    if (!mpCurrentShape)
    {
        window.text("There is no shape in the editor");
        return;
    }

    auto polygon = mpCurrentShape->getOutlines()[outlineIndex];
    std::vector<Vertex> vertices = polygon.getVertices();

    window.text("Vertex Editor");
    bool showDeleteButtons = vertices.size() > 3;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        WithImGuiId vertexId(static_cast<int>(i));
        float2 point = vertices[i];
        if (pointEntry(window, point, i))
        {
            mpEditor->addCommand(UpdateVertexStackCommand::create(outlineIndex, i, point));
        }
        if (showDeleteButtons && window.button("Delete Vertex", true))
        {
            mpEditor->addCommand(DeleteVertexStackCommand::create(outlineIndex, i));
        }
    }
}
void GuiShapeActionsMenu::showGroupControls(size_t outlineIndex, Gui::Group &window)
{
    {
        WithImGuiId id("GroupControlSection");
        if (window.button("Delete Outline"))
        {
            mpEditor->addCommand(DeleteOutlineStackCommand::create(outlineIndex));
        }

        window.text("Add New Vertex");
        window.var("", mNewPoint);
        if (window.button("Add Vertex", true))
        {
            mpEditor->addCommand(AddVertexStackCommand::create(outlineIndex, mNewPoint));
            mNewPoint = float2{0};
        }
    }
    {
        WithImGuiId id(2);
        window.var("", mOutlineOffset);
        if (window.button("Offset Outline", true))
        {
            auto firstPoint = mpCurrentShape->getOutlines()[outlineIndex].getVertices().front();
            auto toPoint = firstPoint + Vertex(mOutlineOffset);
            mpEditor->addCommand(MoveOutlineStackCommand::create(outlineIndex, firstPoint, toPoint));
        }
    }
}
