#pragma once

#include "../../Polygon/Polygon.h"
#include "Falcor.h"
#include "PolygonRendererProperty.h"

namespace psdf
{
using namespace Falcor;

class PolygonRenderer
{
  public:
    using SharedPtr = std::shared_ptr<PolygonRenderer>;

    void render(RenderContext *pRenderContext);
    void transform(const float4x4 &transform);
    void setProperty(const PolygonRendererProperty &rendererProperty);
    void markDirty();
    virtual void setPolygon(const Polygon::SharedPtr &pPolygon);
    virtual void setFbo(const Fbo::SharedPtr &pFbo) = 0;
    virtual float4x4 getTransform() const = 0;

    virtual ~PolygonRenderer() = default;

  protected:
    virtual void init() = 0;
    virtual void uploadPolygonData() = 0;
    virtual void renderImpl(RenderContext *pRenderContext) = 0;
    virtual void transformImpl() = 0;
    virtual void setPropertyImpl(const PolygonRendererProperty &rendererProperty) = 0;

  private:
    void ensureInitialized();

  protected:
    float4x4 mTransform = rmcv::identity<float4x4>();
    Polygon::SharedPtr mpPolygon = nullptr;

  private:
    bool mIsMarkedDirty = false;
    bool mInitialized = false;
};

} // namespace psdf
