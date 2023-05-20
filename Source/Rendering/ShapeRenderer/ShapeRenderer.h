#pragma once

#include "../../Shape/Shape.h"
#include "Falcor.h"
#include "ShapeRendererProperty.h"

namespace psdf
{
using namespace Falcor;

class ShapeRenderer
{
  public:
    using SharedPtr = std::shared_ptr<ShapeRenderer>;

    void render(RenderContext *pRenderContext);
    void transform(const float4x4 &transform);
    void setProperty(const ShapeRendererProperty &rendererProperty);
    void markDirty();
    virtual void setShape(const Shape::SharedPtr &pShape);
    virtual void setFbo(const Fbo::SharedPtr &pFbo) = 0;
    virtual float4x4 getTransform() const = 0;

    virtual ~ShapeRenderer() = default;

  protected:
    virtual void init() = 0;
    virtual void uploadShapeData() = 0;
    virtual void renderImpl(RenderContext *pRenderContext) = 0;
    virtual void transformImpl() = 0;
    virtual void setPropertyImpl(const ShapeRendererProperty &rendererProperty) = 0;

  private:
    void ensureInitialized();

  protected:
    float4x4 mTransform = rmcv::identity<float4x4>();
    Shape::SharedPtr mpShape = nullptr;

  private:
    bool mIsMarkedDirty = false;
    bool mInitialized = false;
};

} // namespace psdf
