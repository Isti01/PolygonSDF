#pragma once

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

  private:
    CoordinateUtil() = default;
};

} // namespace psdf
