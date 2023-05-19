#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/MoveOutlineStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test MoveOutlineStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));

    pEditor->addCommand(psdf::MoveOutlineStackCommand::create(1, {0, 0}, {1, 1}));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape->getOutlines()[1].getVertices()[0] == (outline.getVertices()[0] + 1.0));
}
