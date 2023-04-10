#include "SdfAlgorithmOutputRenderer.h"
#include "../../../Util/RangeGenerator.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmOutputRenderer::SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

SdfAlgorithmOutputRenderer::SharedPtr SdfAlgorithmOutputRenderer::create(GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new SdfAlgorithmOutputRenderer(std::move(pGraphicsState)));
}

void SdfAlgorithmOutputRenderer::init()
{
    mpProgramVars = GraphicsVars::create(mpGraphicsState->getProgram().get());
}

float4x4 SdfAlgorithmOutputRenderer::getTransform() const
{
    return mTransform;
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", offsetof(RegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(RegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmOutputRenderer::uploadPolygonData()
{
    if (!mpPolygon->getAlgorithmOutput())
    {
        return;
    }

    std::vector<RegionBoundVertex> vertices;
    std::vector<uint32_t> indices;
    for (const auto &region : mpPolygon->getAlgorithmOutput()->getPointRegions())
    {
        region.createMesh(vertices, indices, region.getPoint());
    }

    mpPointRegionRenderObject = RenderObject::create(vertices, indices, getVertexLayout());

    vertices.clear();
    indices.clear();
    for (const auto &region : mpPolygon->getAlgorithmOutput()->getLineRegions())
    {
        region.createMesh(vertices, indices, region.getSegment().getPoint1());
    }

    mpLineRegionRenderObject = RenderObject::create(vertices, indices, getVertexLayout());
}

void SdfAlgorithmOutputRenderer::renderImpl(RenderContext *context)
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpPointRegionRenderObject);
    FALCOR_ASSERT(mpLineRegionRenderObject);

    mpGraphicsState->setVao(mpPointRegionRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpPointRegionRenderObject->indexCount, 0, 0);

    mpGraphicsState->setVao(mpLineRegionRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpLineRegionRenderObject->indexCount, 0, 0);
}

void SdfAlgorithmOutputRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    const float4x4 correction = rmcv::translate(float3{-1, -1, 0}) * rmcv::scale(float3{2, 2, 1});
    const auto transform = correction * mTransform;

    float4x4 projection{1};
    if (mFboWidth != 0)
    {
        projection = rmcv::perspective(70, float(mFboWidth) / float(mFboHeight), 0.1f, 250.0f);
    }
    auto view = rmcv::lookAt(float3(0, 0, -10), float3(0, 0, 0), float3(0, 1, 0));
    mpProgramVars["Data"]["iTransform"] = projection * view * transform;
}

void SdfAlgorithmOutputRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
    mFboWidth = pFbo->getWidth();
    mFboHeight = pFbo->getHeight();
    transformImpl();
}
