#pragma once

#include "ShapeRendererProperty.h"

#include <vector>

namespace psdf
{

struct RendererProperties
{
    static constexpr const char *kPolygonOutlineRendererEnabledProperty = "PolygonOutlineRendererEnabledProperty";
    static constexpr const char *kPolygonOutlineColorProperty = "kPolygonOutlineColorProperty";
    static constexpr const char *kFullScreenPolygonRendererEnabledProperty = "FullScreenPolygonRendererEnabledProperty";
    static constexpr const char *kPositiveColorProperty = "kPositiveColorProperty";
    static constexpr const char *kNegativeColorProperty = "kNegativeColorProperty";
    static constexpr const char *kContourFrequencyProperty = "kContourFrequencyProperty";
    static constexpr const char *kContourIntensityProperty = "kContourIntensityProperty";
    static constexpr const char *kDisplayShadowsProperty = "kDisplayShadowsProperty";
    static constexpr const char *kShadowsIntensityProperty = "kShadowsIntensityProperty";
    static constexpr const char *kDisplayCloserToVertexProperty = "kDisplayCloserToVertexProperty";
    static constexpr const char *kShouldDisplayContoursProperty = "kShouldDisplayContoursProperty";
    static constexpr const char *kShouldColorBetweenContoursProperty = "kShouldColorBetweenContoursProperty";
    static constexpr const char *kAlgorithmVisualizationCuttingPointCount = "kAlgorithmVisualizationCuttingPointCount";
    static constexpr const char *kUseCustomDepthCalculation = "kUseCustomDepthCalculation";
    static constexpr const char *kDepthRangeScaling = "kDepthRangeScaling";
    static const std::vector<ShapeRendererProperty> kInitialProperties;

  private:
    RendererProperties() = default;
};

} // namespace psdf
