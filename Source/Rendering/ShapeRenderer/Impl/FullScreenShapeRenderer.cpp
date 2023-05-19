#include "FullScreenShapeRenderer.h"
#include "../RendererProperties.h"

using namespace Falcor;
using namespace psdf;

FullScreenShapeRenderer::FullScreenShapeRenderer(GraphicsState::SharedPtr pGraphicsState)
    : mpGraphicsState(std::move(pGraphicsState))
{
}

FullScreenShapeRenderer::SharedPtr FullScreenShapeRenderer::create(GraphicsState::SharedPtr pGraphicsState)
{
    return SharedPtr(new FullScreenShapeRenderer(std::move(pGraphicsState)));
}

float4x4 FullScreenShapeRenderer::getTransform() const
{
    return mTransform;
}

void FullScreenShapeRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    mpFullscreenTriangle->setFbo(pFbo);
}

void FullScreenShapeRenderer::init()
{
    mpFullscreenTriangle = FullScreenTriangle::create(mpGraphicsState);
    mpFullscreenTriangle->init();
    mpGraphicsVars = mpFullscreenTriangle->getGraphicsVars();
}

void FullScreenShapeRenderer::uploadShapeData()
{
    auto edges = mpShape->getAllFloatEdges();
    auto pEdgeBuffer =
        Buffer::createStructured(mpGraphicsVars["edges"], edges.size(), Resource::BindFlags::ShaderResource,
                                 Buffer::CpuAccess::None, edges.data(), false);

    mpGraphicsVars->setBuffer("edges", pEdgeBuffer);
}

void FullScreenShapeRenderer::renderImpl(RenderContext *pRenderContext)
{
    if (!mEnabled)
    {
        return;
    }

    mpFullscreenTriangle->render(pRenderContext);
}

void FullScreenShapeRenderer::transformImpl()
{
    const float4x4 correction = rmcv::translate(float3{.5, .5, 0}) * rmcv::scale(float3{.5, .5, 1});

    // we need the inverse, because we are transforming the origin instead of the objects
    mpGraphicsVars["Data"]["iTransform"] = rmcv::inverse(correction * mTransform);
}

void FullScreenShapeRenderer::setPropertyImpl(const ShapeRendererProperty &rendererProperty)
{
    if (rendererProperty.key == RendererProperties::kFullScreenPolygonRendererEnabledProperty)
    {
        if (auto *enabled = std::get_if<bool>(&rendererProperty.value))
        {
            mEnabled = *enabled;
        }
    }
    else if (rendererProperty.key == RendererProperties::kPositiveColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iPositiveColor"] = *color;
        }
    }
    else if (rendererProperty.key == RendererProperties::kNegativeColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iNegativeColor"] = *color;
        }
    }
    else if (rendererProperty.key == RendererProperties::kContourFrequencyProperty)
    {
        if (auto *frequency = std::get_if<float>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iContourFrequency"] = *frequency;
        }
    }
    else if (rendererProperty.key == RendererProperties::kContourIntensityProperty)
    {
        if (auto *intensity = std::get_if<float>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iContourIntensity"] = *intensity;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDisplayShadowsProperty)
    {
        if (auto *display = std::get_if<bool>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iDisplayShadows"] = *display;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShadowsIntensityProperty)
    {
        if (auto *intensity = std::get_if<float>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iShadowIntensity"] = *intensity;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDisplayCloserToVertexProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iDisplayCloserToVertex"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShouldDisplayContoursProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iShouldDisplayContours"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShouldColorBetweenContoursProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpGraphicsVars["DistanceColoring"]["iShouldColorBetweenContours"] = *shouldDisplay;
        }
    }
}
