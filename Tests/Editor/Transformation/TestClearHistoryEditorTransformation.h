#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/SetShapeStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/Transformation/ClearHistoryEditorTransformation.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test ClearHistoryEditorTransformation")
{
    auto pStack = psdf::EditorStack::create({psdf::StackEntry::kEmptyStackEntry, psdf::StackEntry::kEmptyStackEntry});
    auto pEditor = psdf::Editor::create(pStack);
    auto pConsumer = psdf::TestConsumer::create();
    auto pCommand = psdf::SetShapeStackCommand::create(psdf::Shape::kSquareShape);

    pEditor->addCommand(pCommand);
    pEditor->addConsumer(pConsumer);
    pEditor->transform(psdf::ClearHistoryEditorTransformation::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "StackTransformedEvent(ClearHistoryEditorTransformation)");

    REQUIRE(pStack->getSize() == 1);
    REQUIRE(pStack->peek()->pShape.get() == psdf::Shape::kSquareShape.get());
    REQUIRE(pStack->peek()->pCommand->getName() == pCommand->getName());
}
