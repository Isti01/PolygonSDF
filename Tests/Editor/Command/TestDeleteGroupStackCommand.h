#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeleteGroupStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeleteGroupStackCommand")
{
    psdf::SubPolygon group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Polygon::create({group, group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));

    pEditor->addCommand(psdf::DeleteGroupStackCommand::create(1));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon->getPolygons().size() == 1);
}
