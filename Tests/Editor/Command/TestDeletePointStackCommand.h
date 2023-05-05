#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeletePointStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeletePointStackCommand")
{
    psdf::SubPolygon group{{{1, 2}, {3, 4}, {5, 1}, {1, 1}}};
    auto pPolygon = psdf::Polygon::create({group, group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));

    pEditor->addCommand(psdf::DeletePointStackCommand::create(0, 0));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon->getPolygons()[0].getPoints().size() == 3);
    REQUIRE(top->polygon->getPolygons()[1].getPoints().size() == 4);
}
