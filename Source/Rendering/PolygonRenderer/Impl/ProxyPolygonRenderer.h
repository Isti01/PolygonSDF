#include "../PolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class ProxyPolygonRenderer : public PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<ProxyPolygonRenderer>;

    float4x4 getTransform() const override;

    void setFbo(const Fbo::SharedPtr &pFbo) override;
    void setPolygon(const Polygon::SharedPtr &pPolygon) override;

  protected:
    ProxyPolygonRenderer(PolygonRenderer::SharedPtr pPolygonRenderer);
    void init() override;
    void uploadPolygonData() override;
    void renderImpl(RenderContext *pRenderContext) override;
    void transformImpl() override;

  protected:
    PolygonRenderer::SharedPtr mpPolygonRenderer;
};

} // namespace psdf
