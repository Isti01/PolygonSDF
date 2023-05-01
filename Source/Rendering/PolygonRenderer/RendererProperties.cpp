#include "RendererProperties.h"

using namespace psdf;

const std::vector<PolygonRendererProperty> RendererProperties::kInitialProperties = {
    {RendererProperties::kPolygonOutlineRendererEnabledProperty, true},
    {RendererProperties::kFullScreenPolygonRendererEnabledProperty, true},
    {RendererProperties::kPositiveColorProperty, float3(0.9, 0.6, 0.3)},
    {RendererProperties::kNegativeColorProperty, float3(0.65, 0.85, 1.0)},
    {RendererProperties::kContourFrequencyProperty, 150.0f},
    {RendererProperties::kContourIntensityProperty, 0.2f},
    {RendererProperties::kDisplayShadowsProperty, true},
    {RendererProperties::kShadowsIntensityProperty, 5.0f},
    {RendererProperties::kDisplayCloserToVertexProperty, true},
    {RendererProperties::kShouldDisplayContoursProperty, true},
    {RendererProperties::kShouldColorBetweenContoursProperty, true},
    {RendererProperties::kAlgorithmVisualizationCuttingPointCount, size_t(100)},
};
