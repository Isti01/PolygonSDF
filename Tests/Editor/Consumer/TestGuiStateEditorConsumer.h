#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Consumer/GuiStateEditorConsumer.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/PublishedEvent/HideGuiPublishedEvent.h"
#include "../../../Source/Editor/PublishedEvent/ShowGuiPublishedEvent.h"

TEST_CASE("Test GuiStateEditorConsumer")
{
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConsumer = psdf::GuiStateEditorConsumer::create();

    pEditor->addConsumer(pConsumer);

    pEditor->publishEvent(psdf::ShowGuiPublishedEvent::create(), nullptr);
    REQUIRE(pConsumer->isGuiEnabled());

    pEditor->publishEvent(psdf::HideGuiPublishedEvent::create(), nullptr);
    REQUIRE(!pConsumer->isGuiEnabled());
}
