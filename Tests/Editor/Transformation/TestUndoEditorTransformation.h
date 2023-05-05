#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/SetPolygonStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/Transformation/UndoEditorTransformation.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test TestUndoEditorTransformation")
{
    auto pStack = psdf::EditorStack::create();
    auto pEditor = psdf::Editor::create(pStack);
    auto pConsumer = psdf::TestConsumer::create();
    auto pFirstCommand = psdf::SetPolygonStackCommand::create(psdf::Polygon::kSquarePolygon);
    auto pSecondCommand = psdf::SetPolygonStackCommand::create(psdf::Polygon::kExamplePolygon);

    pEditor->addCommand(pFirstCommand);
    pEditor->addCommand(pSecondCommand);
    pEditor->addConsumer(pConsumer);
    pEditor->transform(psdf::UndoEditorTransformation::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "StackTransformedEvent(UndoEditorTransformation)");

    REQUIRE(pStack->getSize() == 1);
    REQUIRE(pStack->peek()->command.get() == pFirstCommand.get());
    REQUIRE(pStack->peek()->polygon.get() == psdf::Polygon::kSquarePolygon.get());
}
