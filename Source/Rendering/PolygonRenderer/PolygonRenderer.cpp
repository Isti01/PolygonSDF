#include "PolygonRenderer.h"

using namespace Falcor;
using namespace psdf;

void PolygonRenderer::setPolygon(const Polygon::SharedPtr &polygon)
{
    FALCOR_ASSERT(polygon);
    ensureInitialized();

    bool shouldReUpload = polygon != mpPolygon;
    mpPolygon = polygon;
    if (shouldReUpload)
    {
        uploadPolygonData();
    }
}

void PolygonRenderer::render(RenderContext *context)
{
    FALCOR_ASSERT(context);
    ensureInitialized();

    FALCOR_ASSERT(mpPolygon);
    renderImpl(context);
}

void PolygonRenderer::transform(const float4x4 &transform)
{
    ensureInitialized();
    mTransform = transform;
    transformImpl();
}

void PolygonRenderer::ensureInitialized()
{
    if (mInitialized)
    {
        return;
    }

    init();
    mInitialized = true;
    transform(mTransform);
}
