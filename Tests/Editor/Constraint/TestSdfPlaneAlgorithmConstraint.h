#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/AddNewOutlineStackCommand.h"
#include "../../../Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test SdfPlaneAlgorithmConstraint")
{
    psdf::Outline outline{{{1, 2}, {1, 4}, {1, 2}, {0, 0}}};
    auto pShape = psdf::Shape::create({outline});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pShape}}));
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(psdf::SdfPlaneAlgorithmConstraint::create());
    pEditor->addCommand(psdf::CalculateSdfPlaneAlgorithmCommand::create(psdf::kDefaultSdfPlaneAlgorithmExecutionDesc));
    pEditor->removeConsumer(pConsumer);

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(SdfPlaneAlgorithmConstraint)");
}
