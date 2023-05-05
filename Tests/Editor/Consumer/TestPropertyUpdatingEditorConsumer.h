#pragma once

#include "catch.hpp"

#include "../../../Source/Editor/Consumer/PropertyUpdatingEditorConsumer.h"
#include "../../../Source/Editor/Core/Editor.h"
#include "../../../Source/Editor/PublishedEvent/RendererPropertyPublishedEvent.h"
#include "../../../Source/Rendering/PolygonRenderer/Impl/EmptyPolygonRenderer.h"

TEST_CASE("Test PropertyUpdatingEditorConsumer")
{
    struct TestRenderer : public psdf::EmptyPolygonRenderer
    {
        using SharedPtr = std::shared_ptr<TestRenderer>;
        static SharedPtr create()
        {
            return SharedPtr(new TestRenderer());
        }

        std::vector<psdf::PolygonRendererProperty> getProperties() const
        {
            return mProperties;
        }

      protected:
        TestRenderer() = default;

        void setPropertyImpl(const psdf::PolygonRendererProperty &rendererProperty) override
        {
            mProperties.push_back(rendererProperty);
        }

      private:
        std::vector<psdf::PolygonRendererProperty> mProperties;
    };

    auto pRenderer = TestRenderer::create();
    auto pEditor = psdf::Editor::create(psdf::EditorStack::create());
    auto pConsumer = psdf::PropertyUpdatingEditorConsumer::create(pRenderer);

    pEditor->addConsumer(pConsumer);
    pEditor->publishEvent(psdf::RendererPropertyPublishedEvent::create({"hello world", true}), nullptr);

    auto properties = pRenderer->getProperties();
    REQUIRE(properties.size() == 1);

    auto property = properties[0];
    REQUIRE(property.key == "hello world");
    REQUIRE(std::get_if<bool>(&property.value) != nullptr);
    REQUIRE(*std::get_if<bool>(&property.value));
}
