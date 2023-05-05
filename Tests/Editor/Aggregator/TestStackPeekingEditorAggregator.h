#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Aggregator/StackPeekingEditorAggregator.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../Util/TestCommand.h"

TEST_CASE("Test StackPeekingEditorAggregator for empty stack")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();
    REQUIRE(pAggregator->peekEditor(pEditor)->getEntry().command == psdf::StackEntry::kEmptyStackEntry.command);
    REQUIRE(pAggregator->peekEditor(pEditor)->getEntry().polygon == psdf::StackEntry::kEmptyStackEntry.polygon);
}

TEST_CASE("Test StackPeekingEditorAggregator for stack with entries")
{
    auto pStartPolygon = psdf::Polygon::kSquarePolygon;
    psdf::StackCommand::SharedPtr pStartCommand = psdf::TestCommand::create();
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{pStartCommand, pStartPolygon}}));
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();
    REQUIRE(pAggregator->peekEditor(pEditor)->getEntry().command == pStartCommand);
    REQUIRE(pAggregator->peekEditor(pEditor)->getEntry().polygon == pStartPolygon);
}
