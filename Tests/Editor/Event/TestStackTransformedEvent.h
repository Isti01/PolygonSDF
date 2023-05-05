#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/Transformation/ClearHistoryEditorTransformation.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test StackTransformedEvent")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->transform(psdf::ClearHistoryEditorTransformation::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "StackTransformedEvent(ClearHistoryEditorTransformation)");
}
