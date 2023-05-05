#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/MergePolygonWithOffsetStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test MergePolygonWithOffsetStackCommand")
{
    psdf::SubPolygon group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Polygon::create({group, group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));

    pEditor->addCommand(psdf::MergePolygonWithOffsetStackCommand::create(pPolygon, {1, 1}));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon->getPolygons().size() == 4);
    REQUIRE(top->polygon->getPolygons()[3].getPoints()[0] == (group.getPoints()[0] + 1.0));
}
