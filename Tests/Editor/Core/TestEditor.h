#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/PublishedEvent/ShowGuiPublishedEvent.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test Editor::publishEvent")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    psdf::PublishedEvent::SharedPtr pPublishedEvent = psdf::ShowGuiPublishedEvent::create();
    auto pTestConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pTestConsumer);
    pEditor->publishEvent(pPublishedEvent, nullptr);
    pEditor->removeConsumer(pTestConsumer);

    REQUIRE(pTestConsumer->getAcceptedEvents().size() == 1);
}


TEST_CASE("Test Editor::addCommand")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pCommand = psdf::TestCommand::create();

    pEditor->addCommand(pCommand);
    auto top = pEditor->getEditorStack()->peek();

    REQUIRE(top);
    REQUIRE(top->polygon == nullptr);
    REQUIRE(top->command.get() == pCommand.get());
}
