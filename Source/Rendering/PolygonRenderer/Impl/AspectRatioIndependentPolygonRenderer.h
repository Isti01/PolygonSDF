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

  private:
    void updateAspectRatio();

  private:
    float mAspectRatio = 1;
};

} // namespace psdf
