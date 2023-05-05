#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Command/SetPolygonStackCommand.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/Transformation/ClearHistoryEditorTransformation.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test ClearHistoryEditorTransformation")
{
    auto pStack = psdf::EditorStack::create({psdf::StackEntry::kEmptyStackEntry, psdf::StackEntry::kEmptyStackEntry});
    auto pEditor = psdf::Editor::create(pStack);
    auto pConsumer = psdf::TestConsumer::create();
    auto pCommand = psdf::SetPolygonStackCommand::create(psdf::Polygon::kSquarePolygon);

    pEditor->addCommand(pCommand);
    pEditor->addConsumer(pConsumer);
    pEditor->transform(psdf::ClearHistoryEditorTransformation::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "StackTransformedEvent(ClearHistoryEditorTransformation)");

    REQUIRE(pStack->getSize() == 1);
    REQUIRE(pStack->peek()->polygon.get() == psdf::Polygon::kSquarePolygon.get());
    REQUIRE(pStack->peek()->command->getName() == pCommand->getName());
}
