#include "RendererProperties.h"

using namespace psdf;

const std::vector<ShapeRendererProperty> RendererProperties::kInitialProperties = {
    {RendererProperties::kPolygonOutlineRendererEnabledProperty, false},
    {RendererProperties::kPolygonOutlineColorProperty, float3(1, 1, 1)},
    {RendererProperties::kFullScreenPolygonRendererEnabledProperty, true},
    {RendererProperties::kPositiveColorProperty, float3(0.9, 0.6, 0.3)},
    {RendererProperties::kNegativeColorProperty, float3(0.65, 0.85, 1.0)},
    {RendererProperties::kShouldDisplayContoursProperty, true},
    {RendererProperties::kShouldColorBetweenContoursProperty, true},
    {RendererProperties::kContourFrequencyProperty, 150.0f},
    {RendererProperties::kContourIntensityProperty, 0.2f},
    {RendererProperties::kDisplayCloserToVertexProperty, true},
    {RendererProperties::kDisplayShadowsProperty, true},
    {RendererProperties::kShadowsIntensityProperty, 5.0f},
    {RendererProperties::kAlgorithmVisualizationCuttingPointCount, size_t(100)},
    {RendererProperties::kUseCustomDepthCalculation, true},
    {RendererProperties::kDepthRangeScaling, 100.0f},
};
