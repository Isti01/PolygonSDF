#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/UpdateVertexStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test UpdateVertexStackCommand")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline, outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));

    psdf::Vertex newVertex{42, 42};
    pEditor->addCommand(psdf::UpdateVertexStackCommand::create(1, 1, newVertex));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape->getOutlines()[1].getVertices()[1] == newVertex);
}
