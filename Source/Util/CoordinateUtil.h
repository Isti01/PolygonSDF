#pragma once

#include "../Polygon/Polygon.h"
#include "../Polygon/SubPolygon.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class CoordinateUtil
{
  public:
    static float2 screenToSceneSpaceCoordinate(const float4x4 &transform, float2 coords);
    static float2 sceneToScreenSpaceCoordinate(const float4x4 &transform, float2 coords);
    static std::optional<size_t> findClosestInSubPolygon(const Polygon::Points &points, Point point);
    static std::optional<std::pair<size_t, size_t>> findClosestPointIndex(const std::vector<SubPolygon> &polygons,
                                                                          Point point);

  private:
    CoordinateUtil() = default;
};

} // namespace psdf
