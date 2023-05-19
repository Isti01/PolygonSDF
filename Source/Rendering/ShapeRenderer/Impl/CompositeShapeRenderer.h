#pragma once

#include "../ShapeRenderer.h"

namespace psdf
{
using namespace Falcor;

class CompositeShapeRenderer : public ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<CompositeShapeRenderer>;

    static SharedPtr create(std::vector<ShapeRenderer::SharedPtr> renderers);

    float4x4 getTransform() const override;

    void setShape(const Shape::SharedPtr &pPolygon) override;
    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void transformImpl() override;

  protected:
    CompositeShapeRenderer(std::vector<ShapeRenderer::SharedPtr> renderers);

    void init() override;
    void uploadShapeData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;

  private:
    std::vector<ShapeRenderer::SharedPtr> mRenderers;
};

} // namespace psdf
