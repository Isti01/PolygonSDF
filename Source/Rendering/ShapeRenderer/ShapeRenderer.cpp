#include "ShapeRenderer.h"

using namespace Falcor;
using namespace psdf;

void ShapeRenderer::setShape(const Shape::SharedPtr &pShape)
{
    FALCOR_ASSERT(pShape);
    ensureInitialized();

    bool shouldReUpload = pShape != mpShape;
    mpShape = pShape;
    if (shouldReUpload)
    {
        uploadShapeData();
    }
}

void ShapeRenderer::render(RenderContext *context)
{
    FALCOR_ASSERT(context);
    ensureInitialized();
    if (mIsMarkedDirty)
    {
        transform(mTransform);
        uploadShapeData();
        mIsMarkedDirty = false;
    }

    FALCOR_ASSERT(mpShape);
    renderImpl(context);
}

void ShapeRenderer::transform(const float4x4 &transform)
{
    ensureInitialized();
    mTransform = transform;
    transformImpl();
}

void ShapeRenderer::setProperty(const ShapeRendererProperty &rendererProperty)
{
    ensureInitialized();
    setPropertyImpl(rendererProperty);
}

void ShapeRenderer::ensureInitialized()
{
    if (mInitialized)
    {
        return;
    }

    init();
    mInitialized = true;
    transform(mTransform);
}

void ShapeRenderer::markDirty()
{
    mIsMarkedDirty = true;
}
