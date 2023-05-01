#pragma once

#include "../../Rendering/PolygonRenderer/PolygonRenderer.h"
#include "../Core/EditorConsumer.h"

namespace psdf
{

class PropertyUpdatingEditorConsumer : public EditorConsumer
{
  public:
    using SharedPtr = std::shared_ptr<PropertyUpdatingEditorConsumer>;

    static SharedPtr create(PolygonRenderer::SharedPtr pRenderer);

    void accept(const EditorEvent::SharedPtr &pEvent) override;

  protected:
    PropertyUpdatingEditorConsumer(PolygonRenderer::SharedPtr pRenderer);

  private:
    PolygonRenderer::SharedPtr mpRenderer;
};

} // namespace psdf
