#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/DeleteGroupStackCommand.h"
#include "../../../Source/Editor/Constraint/DeleteGroupEditorConstraint.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test DeleteGroupEditorConstraint")
{
    psdf::SubPolygon group{{{1, 2}, {3, 4}, {5, 1}}};
    auto pPolygon = psdf::Polygon::create({group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(psdf::DeleteGroupEditorConstraint::create());
    pEditor->addCommand(psdf::DeleteGroupStackCommand::create(0));
    pEditor->removeConsumer(pConsumer);

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(DeleteGroupEditorConstraint)");
}
