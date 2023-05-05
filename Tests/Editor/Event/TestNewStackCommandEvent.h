#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Core/Editor.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test NewStackCommandEvent")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addCommand(psdf::TestCommand::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "NewStackCommandEvent(TestCommand)");
}
