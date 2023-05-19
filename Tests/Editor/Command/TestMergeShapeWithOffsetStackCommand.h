#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/MergeShapeWithOffsetStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test MergeShapeWithOffsetStackCommand")
{
    psdf::Outline group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Shape::create({group, group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));

    pEditor->addCommand(psdf::MergeShapeWithOffsetStackCommand::create(pPolygon, {1, 1}));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape->getOutlines().size() == 4);
    REQUIRE(top->pShape->getOutlines()[3].getVertices()[0] == (group.getVertices()[0] + 1.0));
}
