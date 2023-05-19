#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Aggregator/StackSizeEditorAggregator.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test StackSizeEditorAggregator for empty stack")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pAggregator = psdf::StackSizeEditorAggregator::create();
    REQUIRE(pAggregator->getEditorStackSize(pEditor)->getSize() == 0);
}

TEST_CASE("Test StackSizeEditorAggregator for stack with entries")
{
    auto pStartPolygon = psdf::Shape::kSquareShape;
    psdf::StackCommand::SharedPtr pStartCommand = psdf::TestCommand::create();
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{pStartCommand, pStartPolygon}}));
    auto pAggregator = psdf::StackSizeEditorAggregator::create();
    REQUIRE(pAggregator->getEditorStackSize(pEditor)->getSize() == 1);
}
