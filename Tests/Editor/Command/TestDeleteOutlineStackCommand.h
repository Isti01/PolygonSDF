#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeleteOutlineStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeleteOutlineStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();


    pEditor->addCommand(psdf::DeleteOutlineStackCommand::create(1));
    auto top = pAggregator->peekEditor(pEditor);

    REQUIRE(top);
    REQUIRE(top->getEntry().pShape->getOutlines().size() == 1);
}
