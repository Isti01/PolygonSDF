#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Constraint/DeleteVertexEditorConstraint.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeleteVertexEditorConstraint")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(psdf::DeleteVertexEditorConstraint::create());
    pEditor->addCommand(psdf::DeleteVertexStackCommand::create(0, 0));
    pEditor->removeConsumer(pConsumer);

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(DeleteVertexEditorConstraint)");
}
