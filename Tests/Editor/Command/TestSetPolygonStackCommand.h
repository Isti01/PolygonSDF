#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/SetPolygonStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test SetPolygonStackCommand")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());

    pEditor->addCommand(psdf::SetPolygonStackCommand::create(psdf::Polygon::kExamplePolygon));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon.get() == psdf::Polygon::kExamplePolygon.get());
}
