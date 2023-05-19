#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/SetShapeStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/Transformation/UndoEditorTransformation.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test TestUndoEditorTransformation")
{
    auto pStack = psdf::EditorStack::create();
    auto pEditor = psdf::Editor::create(pStack);
    auto pConsumer = psdf::TestConsumer::create();
    auto pFirstCommand = psdf::SetShapeStackCommand::create(psdf::Shape::kSquareShape);
    auto pSecondCommand = psdf::SetShapeStackCommand::create(psdf::Shape::kStarterShape);

    pEditor->addCommand(pFirstCommand);
    pEditor->addCommand(pSecondCommand);
    pEditor->addConsumer(pConsumer);
    pEditor->transform(psdf::UndoEditorTransformation::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "StackTransformedEvent(UndoEditorTransformation)");

    REQUIRE(pStack->getSize() == 1);
    REQUIRE(pStack->peek()->pCommand.get() == pFirstCommand.get());
    REQUIRE(pStack->peek()->pShape.get() == psdf::Shape::kSquareShape.get());
}
