#include <numeric>

#include "../RendererProperties.h"
#include "SdfAlgorithmOutputRenderer.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmOutputRenderer::SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
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
    pBufferLayout->addElement("POS", offsetof(LineRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(LineRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmOutputRenderer::setPolygon(const Polygon::SharedPtr &pPolygon)
{
    PolygonRenderer::setPolygon(pPolygon);
}

void SdfAlgorithmOutputRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    mpProgramVars["Data"]["iTransform"] = mTransform;
}

void SdfAlgorithmOutputRenderer::renderImpl(RenderContext *context)
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpGraphicsState);
    FALCOR_ASSERT(mpProgramVars);
    FALCOR_ASSERT(mpRenderObject);

    mpGraphicsState->setVao(mpRenderObject->pVao);
    context->drawIndexed(mpGraphicsState.get(), mpProgramVars.get(), mpRenderObject->indexCount, 0, 0);
}

void SdfAlgorithmOutputRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpGraphicsState);
    mpGraphicsState->setFbo(pFbo);
}

void SdfAlgorithmOutputRenderer::setPropertyImpl(const PolygonRendererProperty &rendererProperty)
{
    if (rendererProperty.key == RendererProperties::kPositiveColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iPositiveColor"] = *color;
        }
    }
    else if (rendererProperty.key == RendererProperties::kNegativeColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iNegativeColor"] = *color;
        }
    }
    else if (rendererProperty.key == RendererProperties::kContourFrequencyProperty)
    {
        if (auto *frequency = std::get_if<float>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iContourFrequency"] = *frequency;
        }
    }
    else if (rendererProperty.key == RendererProperties::kContourIntensityProperty)
    {
        if (auto *intensity = std::get_if<float>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iContourIntensity"] = *intensity;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDisplayShadowsProperty)
    {
        if (auto *display = std::get_if<bool>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iDisplayShadows"] = *display;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShadowsIntensityProperty)
    {
        if (auto *intensity = std::get_if<float>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iShadowIntensity"] = *intensity;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDisplayCloserToVertexProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iDisplayCloserToVertex"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShouldDisplayContoursProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iShouldDisplayContours"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShouldColorBetweenContoursProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpProgramVars["DistanceColoring"]["iShouldColorBetweenContours"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kAlgorithmVisualizationCuttingPointCount)
    {
        if (auto *pointsToCutAround = std::get_if<size_t>(&rendererProperty.value))
        {
            mPointsToCutAround = *pointsToCutAround;
            markDirty();
        }
    }
}
