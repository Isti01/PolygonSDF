#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeleteOutlineStackCommand.h"
#include "../../../Source/Editor/Constraint/DeleteOutlineEditorConstraint.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test DeleteOutlineEditorConstraint")
{
    psdf::Outline outline{{{1, 2}, {3, 4}, {5, 1}}};
    auto pShape = psdf::Shape::create({outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(psdf::DeleteOutlineEditorConstraint::create());
    pEditor->addCommand(psdf::DeleteOutlineStackCommand::create(0));
    pEditor->removeConsumer(pConsumer);

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(DeleteOutlineEditorConstraint)");
}
