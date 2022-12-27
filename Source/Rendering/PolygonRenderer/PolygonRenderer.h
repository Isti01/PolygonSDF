#pragma once

#include "../../Polygon/Polygon.h"
#include "Falcor.h"

namespace psdf
{
using namespace Falcor;

class PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<PolygonRenderer>;

    void render(RenderContext *pRenderContext);
    void transform(const float4x4 &transform);
    virtual void setPolygon(const Polygon::SharedPtr &pPolygon);
    virtual void setFbo(const Fbo::SharedPtr &pFbo) const = 0;

  protected:
    virtual void init() = 0;
    virtual void uploadPolygonData() = 0;
    virtual void renderImpl(RenderContext *pRenderContext) const = 0;
    virtual void transformImpl() = 0;

  private:
    void ensureInitialized();

  protected:
    float4x4 mTransform = float4x4{1};
    Polygon::SharedPtr mpPolygon = nullptr;

  private:
    bool mInitialized = false;
};

} // namespace psdf
