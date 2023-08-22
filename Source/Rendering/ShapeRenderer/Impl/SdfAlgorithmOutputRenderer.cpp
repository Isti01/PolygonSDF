#include <numeric>

#include "../RendererProperties.h"
#include "SdfAlgorithmOutputRenderer.h"

using namespace Falcor;
using namespace psdf;

SdfAlgorithmOutputRenderer::SdfAlgorithmOutputRenderer(GraphicsState::SharedPtr pModifiedDepthState,
                                                       GraphicsState::SharedPtr pSimpleMeshState)
    : mpModifiedDepthState(std::move(pModifiedDepthState)), mpSimpleMeshState(std::move(pSimpleMeshState))
{
}

void SdfAlgorithmOutputRenderer::init()
{
    mpModifiedDepthProgramVars = GraphicsVars::create(mpModifiedDepthState->getProgram().get());
    mpSimpleMeshProgramVars = GraphicsVars::create(mpSimpleMeshState->getProgram().get());

    setModifiedDepthProgramAsActive();
}

float4x4 SdfAlgorithmOutputRenderer::getTransform() const
{
    return mTransform;
}

static VertexLayout::SharedPtr getVertexLayout()
{
    auto pLayout = VertexLayout::create();
    const auto pBufferLayout = VertexBufferLayout::create();
    pBufferLayout->addElement("POS", offsetof(VertexRegionBoundVertex, position), ResourceFormat::RG32Float, 1, 0);
    pBufferLayout->addElement("DST", offsetof(VertexRegionBoundVertex, signedDistance), ResourceFormat::R32Float, 1, 1);
    pLayout->addBufferLayout(0, pBufferLayout);
    return pLayout;
}

void SdfAlgorithmOutputRenderer::setShape(const Shape::SharedPtr &pShape)
{
    ShapeRenderer::setShape(pShape);
}

void SdfAlgorithmOutputRenderer::setModifiedDepthProgramAsActive()
{
    mpActiveState = mpModifiedDepthState;
    mpActiveProgramVars = mpModifiedDepthProgramVars;
}

void SdfAlgorithmOutputRenderer::setSimpleMeshProgramAsActive()
{
    mpActiveState = mpSimpleMeshState;
    mpActiveProgramVars = mpSimpleMeshProgramVars;
}

void SdfAlgorithmOutputRenderer::transformImpl()
{
    FALCOR_ASSERT(mpModifiedDepthProgramVars);
    FALCOR_ASSERT(mpSimpleMeshProgramVars);

    mpModifiedDepthProgramVars["Data"]["iTransform"] = mTransform;
    mpSimpleMeshProgramVars["Data"]["iTransform"] = mTransform;
}

void SdfAlgorithmOutputRenderer::renderImpl(RenderContext *context)
{
    FALCOR_ASSERT(context);

    FALCOR_ASSERT(mpActiveState);
    FALCOR_ASSERT(mpModifiedDepthProgramVars);
    FALCOR_ASSERT(mpSimpleMeshProgramVars);
    if (!mpRenderObject)
    {
        return;
    }
    mpActiveState->setVao(mpRenderObject->pVao);
    context->drawIndexed(mpActiveState.get(), mpActiveProgramVars.get(), mpRenderObject->indexCount, 0, 0);
}

void SdfAlgorithmOutputRenderer::setFbo(const Fbo::SharedPtr &pFbo)
{
    FALCOR_ASSERT(mpActiveState);
    mpActiveState->setFbo(pFbo);
}
void SdfAlgorithmOutputRenderer::setPropertyImpl(const ShapeRendererProperty &rendererProperty)
{
    if (rendererProperty.key == RendererProperties::kPositiveColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iPositiveColor"] = *color;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iPositiveColor"] = *color;
        }
    }
    else if (rendererProperty.key == RendererProperties::kNegativeColorProperty)
    {
        if (auto *color = std::get_if<float3>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iNegativeColor"] = *color;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iNegativeColor"] = *color;
        }
    }
    else if (rendererProperty.key == RendererProperties::kContourFrequencyProperty)
    {
        if (auto *frequency = std::get_if<float>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iContourFrequency"] = *frequency;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iContourFrequency"] = *frequency;
        }
    }
    else if (rendererProperty.key == RendererProperties::kContourIntensityProperty)
    {
        if (auto *intensity = std::get_if<float>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iContourIntensity"] = *intensity;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iContourIntensity"] = *intensity;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDisplayShadowsProperty)
    {
        if (auto *display = std::get_if<bool>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iDisplayShadows"] = *display;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iDisplayShadows"] = *display;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShadowsIntensityProperty)
    {
        if (auto *intensity = std::get_if<float>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iShadowIntensity"] = *intensity;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iShadowIntensity"] = *intensity;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDisplayCloserToVertexProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iDisplayCloserToVertex"] = *shouldDisplay;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iDisplayCloserToVertex"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShouldDisplayContoursProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iShouldDisplayContours"] = *shouldDisplay;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iShouldDisplayContours"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kShouldColorBetweenContoursProperty)
    {
        if (auto *shouldDisplay = std::get_if<bool>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["DistanceColoringSettings"]["iShouldColorBetweenContours"] = *shouldDisplay;
            mpSimpleMeshProgramVars["DistanceColoringSettings"]["iShouldColorBetweenContours"] = *shouldDisplay;
        }
    }
    else if (rendererProperty.key == RendererProperties::kDepthRangeScaling)
    {
        if (auto *depthScaling = std::get_if<float>(&rendererProperty.value))
        {
            mpModifiedDepthProgramVars["Data"]["iDepthScaling"] = *depthScaling;
            mpSimpleMeshProgramVars["Data"]["iDepthScaling"] = *depthScaling;
        }
    }
    else if (rendererProperty.key == RendererProperties::kUseCustomDepthCalculation)
    {
        if (auto *useCustomCalculation = std::get_if<bool>(&rendererProperty.value))
        {
            if (*useCustomCalculation)
            {
                setModifiedDepthProgramAsActive();
            }
            else
            {
                setSimpleMeshProgramAsActive();
            }
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
