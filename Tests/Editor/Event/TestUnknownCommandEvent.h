#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Core/Editor.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test TestUnknownCommandEvent")
{
    class EmptyTestCommand : public psdf::EditorCommand
    {
      public:
        using SharedPtr = std::shared_ptr<EmptyTestCommand>;

        static SharedPtr create()
        {
            return SharedPtr(new EmptyTestCommand());
        }

        std::string getName() const override
        {
            return "EmptyTestCommand";
        }

      protected:
        EmptyTestCommand() = default;
    };

    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addCommand(EmptyTestCommand::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "UnknownCommandEvent(EmptyTestCommand)");
}
