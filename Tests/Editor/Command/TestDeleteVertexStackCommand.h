#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeleteVertexStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeleteVertexStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}, {1, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();

    pEditor->addCommand(psdf::DeleteVertexStackCommand::create(0, 0));
    auto top = pAggregator->peekEditor(pEditor);

    REQUIRE(top);
    REQUIRE(top->getEntry().pShape->getOutlines()[0].getVertices().size() == 3);
    REQUIRE(top->getEntry().pShape->getOutlines()[1].getVertices().size() == 4);
}
