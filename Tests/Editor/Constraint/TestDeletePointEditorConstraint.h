#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Constraint/DeletePointEditorConstraint.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test DeletePointEditorConstraint")
{
    psdf::SubPolygon group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Polygon::create({group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(psdf::DeletePointEditorConstraint::create());
    pEditor->addCommand(psdf::DeletePointStackCommand::create(0, 0));
    pEditor->removeConsumer(pConsumer);

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(DeletePointEditorConstraint)");
}
