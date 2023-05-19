#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/AddNewOutlineStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test TestAddNewOutlineStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));

    pEditor->addCommand(psdf::AddNewOutlineStackCommand::create(outline));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape->getOutlines().size() == 3);
}
