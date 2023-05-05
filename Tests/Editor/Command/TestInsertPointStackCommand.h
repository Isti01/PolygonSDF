#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/InsertPointStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test InsertPointStackCommand")
{
    psdf::SubPolygon group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Polygon::create({group, group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));

    psdf::Point newPoint{1, 1};
    pEditor->addCommand(psdf::InsertPointStackCommand::create(1, 0, newPoint));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon->getPolygons()[1].getPoints().size() == 4);
    REQUIRE(top->polygon->getPolygons()[1].getPoints()[0] == newPoint);
}
