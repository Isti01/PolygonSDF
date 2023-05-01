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

double SdfAlgorithmOutputRenderer::getMaxDistanceFromPointInPolygon(const Point &origin,
                                                                    const Polygon::SharedPtr &pPolygon)
{
    double maxDistance = glm::distance(origin, pPolygon->getPolygons()[0].getPoints()[0]);
    for (const auto &subPolygon : pPolygon->getPolygons())
    {
        for (const auto &point : subPolygon.getPoints())
        {
            maxDistance = glm::max(maxDistance, glm::distance(origin, point));
        }
    }
    return maxDistance;
}

void SdfAlgorithmOutputRenderer::setPolygon(const Polygon::SharedPtr &pPolygon)
{
    if (pPolygon)
    {
        mPolygonCenter = pPolygon->getCenter();
    }
    PolygonRenderer::setPolygon(pPolygon);
}

void SdfAlgorithmOutputRenderer::transformImpl()
{
    FALCOR_ASSERT(mpProgramVars);

    const auto transform = mTransform * rmcv::translate(-float3{mPolygonCenter, 0});

    auto projection = rmcv::identity<float4x4>();
    if (mFboWidth != 0)
    {
        float camWidth = kOrthoCamWidth;
        float camHeight = kOrthoCamWidth / float(mFboWidth) * float(mFboHeight);
        projection = rmcv::ortho(-camWidth, camWidth, -camHeight, camHeight, -250.0f, 250.0f);
    }
    auto view = rmcv::lookAt(float3(0, 0, -1), float3(0, 0, 0), float3(0, 1, 0));
    mpProgramVars["Data"]["iTransform"] = projection * view * transform;
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
    mFboWidth = pFbo->getWidth();
    mFboHeight = pFbo->getHeight();
    transformImpl();
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
