#pragma once

#include "../../Rendering/ShapeRenderer/ShapeRenderer.h"
#include "../Core/EditorConsumer.h"

namespace psdf
{

class PropertyUpdatingEditorConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<PropertyUpdatingEditorConsumer>;

    static SharedPtr create(ShapeRenderer::SharedPtr pRenderer);

    void accept(const EditorEvent::SharedPtr &pEvent) override;

  protected:
    PropertyUpdatingEditorConsumer(ShapeRenderer::SharedPtr pRenderer);

  private:
    ShapeRenderer::SharedPtr mpRenderer;
};

} // namespace psdf
