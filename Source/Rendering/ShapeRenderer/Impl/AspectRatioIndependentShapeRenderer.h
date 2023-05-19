#include "ProxyShapeRenderer.h"

namespace psdf
{
using namespace Falcor;

class AspectRatioIndependentShapeRenderer : public ProxyShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<AspectRatioIndependentShapeRenderer>;

    static SharedPtr create(ShapeRenderer::SharedPtr pShapeRenderer);
    void setFbo(const Fbo::SharedPtr &pFbo) override;

  protected:
    AspectRatioIndependentShapeRenderer(ShapeRenderer::SharedPtr pShapeRenderer);
    void transformImpl() override;
    void setPropertyImpl(const ShapeRendererProperty &rendererProperty) override;

  private:
    void updateAspectRatio();

  private:
    static constexpr float kOrthoCamWidth = 50;

    float mAspectRatio = 0;
};

} // namespace psdf
