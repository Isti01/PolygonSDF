#pragma once

#include "../Polygon/Polygon.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class CoordinateUtil
{
  public:
    static float2 screenToSceneSpaceCoordinate(const float4x4 &transform, float2 coords);
    static float2 sceneToScreenSpaceCoordinate(const float4x4 &transform, float2 coords);
    static float2 screenToSceneSpaceVector(const float4x4 &transform, float2 vector);
    static std::optional<size_t> findClosestPointIndexInPolygon(const Polygon::SharedPtr &polygon, float2 point);

  private:
    CoordinateUtil() = default;
};

} // namespace psdf
