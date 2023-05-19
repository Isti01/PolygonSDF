#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/InsertVertexStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test InsertVertexStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));

    psdf::Vertex newVertex{1, 1};
    pEditor->addCommand(psdf::InsertVertexStackCommand::create(1, 0, newVertex));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape->getOutlines()[1].getVertices().size() == 4);
    REQUIRE(top->pShape->getOutlines()[1].getVertices()[0] == newVertex);
}
