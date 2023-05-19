#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/SetShapeStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test SetShapeStackCommand")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());

    pEditor->addCommand(psdf::SetShapeStackCommand::create(psdf::Shape::kStarterShape));
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->pShape.get() == psdf::Shape::kStarterShape.get());
}
