#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test CalculateSdfPlaneAlgorithmCommand")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({{nullptr, psdf::Polygon::kExamplePolygon}}));

    pEditor->addCommand(psdf::CalculateSdfPlaneAlgorithmCommand::create(psdf::kDefaultSdfPlaneAlgorithmExecutionDesc));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon->getAlgorithmOutput());
}
