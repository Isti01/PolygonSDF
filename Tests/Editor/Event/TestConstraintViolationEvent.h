#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Core/Editor.h"
#include "../../Util/TestCommand.h"
#include "../../Util/TestConsumer.h"

TEST_CASE("Test ConstraintViolationEvent")
{
    class TestEditorConstraint : public psdf::EditorConstraint
    {
      public:
        using SharedPtr = std::shared_ptr<TestEditorConstraint>;

        static SharedPtr create()
        {
            return SharedPtr(new TestEditorConstraint());
        }

        std::string getName() const override
        {
            return "TestEditorConstraint";
        }

        bool evaluate(const psdf::EditorStack::SharedPtr &pStack,
                      const psdf::EditorCommand::SharedPtr &pCommand) override
        {
            return false;
        }

      protected:
        TestEditorConstraint() = default;
    };

    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConstraint = TestEditorConstraint::create();
    auto pConsumer = psdf::TestConsumer::create();

    pEditor->addConsumer(pConsumer);
    pEditor->addConstraint(pConstraint);
    pEditor->addCommand(psdf::TestCommand::create());

    REQUIRE(pConsumer->getAcceptedEvents().size() == 1);
    REQUIRE(pConsumer->getAcceptedEvents()[0]->getName() == "ConstraintViolationEvent(TestEditorConstraint)");
}
