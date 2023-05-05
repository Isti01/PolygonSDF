#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Consumer/VisualEditorStateChangeEditorConsumer.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/PublishedEvent/VisualEditorModeChangedPublishedEvent.h"


TEST_CASE("Test VisualEditorStateChangeEditorConsumer")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConsumer = psdf::VisualEditorStateChangeEditorConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->publishEvent(psdf::VisualEditorModeChangedPublishedEvent::create("hello world"), nullptr);

    REQUIRE(pConsumer->getCurrentState() == "hello world");
}
