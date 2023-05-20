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
    auto pAggregator = psdf::StackPeekingEditorAggregator::create();


    pEditor->addCommand(pCommand);
    auto top = pAggregator->peekEditor(pEditor);

    REQUIRE(top);
    REQUIRE(top->getEntry().pShape == nullptr);
    REQUIRE(top->getEntry().pCommand.get() == pCommand.get());
}
