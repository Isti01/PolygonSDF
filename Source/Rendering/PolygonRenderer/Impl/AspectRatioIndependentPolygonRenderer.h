#include "ProxyPolygonRenderer.h"

namespace psdf
{
using namespace Falcor;

class AspectRatioIndependentPolygonRenderer : public ProxyPolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<AspectRatioIndependentPolygonRenderer>;

    static SharedPtr create(PolygonRenderer::SharedPtr pPolygonRenderer);
    void setFbo(const Fbo::SharedPtr &pFbo) override;

  protected:
    AspectRatioIndependentPolygonRenderer(PolygonRenderer::SharedPtr pPolygonRenderer);
    void transformImpl() override;
    void setPropertyImpl(const PolygonRendererProperty &rendererProperty) override;

  private:
    void updateAspectRatio();

  private:
    static constexpr float kOrthoCamWidth = 50;

    float mAspectRatio = 0;
};

} // namespace psdf
