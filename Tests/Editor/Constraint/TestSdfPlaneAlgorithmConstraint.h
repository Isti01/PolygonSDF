#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/AddNewGroupStackCommand.h"
#include "../../../Source/Editor/Constraint/SdfPlaneAlgorithmConstraint.h"
#include "../../../Source/Editor/Core/Editor.h"

TEST_CASE("Test SdfPlaneAlgorithmConstraint")
{
    psdf::SubPolygon group{{{1, 2}, {1, 4}, {1, 2}, {0, 0}}};
    auto pPolygon = psdf::Polygon::create({group});
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create({psdf::StackEntry{nullptr, pPolygon}}));
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(psdf::SdfPlaneAlgorithmConstraint::create());
    pEditor->addCommand(psdf::CalculateSdfPlaneAlgorithmCommand::create(psdf::kDefaultSdfPlaneAlgorithmExecutionDesc));
    pEditor->removeConsumer(pConsumer);

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(SdfPlaneAlgorithmConstraint)");
}
