#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeleteVertexStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeleteVertexStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}, {1, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));

    pEditor->addCommand(psdf::DeleteVertexStackCommand::create(0, 0));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape->getOutlines()[0].getVertices().size() == 3);
    REQUIRE(top->pShape->getOutlines()[1].getVertices().size() == 4);
}
