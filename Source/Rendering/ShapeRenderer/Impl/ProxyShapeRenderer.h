#include "../ShapeRenderer.h"

namespace psdf
{
using namespace Falcor;

class ProxyShapeRenderer : public ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<ProxyShapeRenderer>;

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void setShape(const Shape::SharedPtr &pPolygon) override;

  protected:
    ProxyShapeRenderer(ShapeRenderer::SharedPtr pPolygonRenderer);
    void init() override;
    void uploadShapeData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void transformImpl() override;

  protected:
    ShapeRenderer::SharedPtr mpRenderer;
};

} // namespace psdf
