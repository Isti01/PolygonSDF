#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/CalculateSdfPlaneAlgorithmCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test CalculateSdfPlaneAlgorithmCommand")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({{nullptr, psdf::Shape::kStarterShape}}));
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();


    pEditor->addCommand(psdf::CalculateSdfPlaneAlgorithmCommand::create(psdf::kDefaultSdfPlaneAlgorithmExecutionDesc));
    auto top = pAggregator->peekEditor(pEditor);

    REQUIRE(top);
    REQUIRE(top->getEntry().pShape->getAlgorithmOutput());
}
