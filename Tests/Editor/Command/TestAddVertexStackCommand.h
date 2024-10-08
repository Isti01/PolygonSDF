#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/AddVertexStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test TestAddVertexStackCommand")
{
    psdf::Outline group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Shape::create({group, group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();

    psdf::Vertex newPoint{1, 1};
    pEditor->addCommand(psdf::AddVertexStackCommand::create(1, newPoint));
    auto top = pAggregator->peekEditor(pEditor);

    REQUIRE(top);
    REQUIRE(top->getEntry().pShape->getOutlines()[1].getVertices().size() == 4);
    REQUIRE(top->getEntry().pShape->getOutlines()[1].getVertices().back() == newPoint);
}
