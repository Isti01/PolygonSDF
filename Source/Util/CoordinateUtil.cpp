#include "CoordinateUtil.h"

using namespace psdf;
using namespace Falcor;

float2 CoordinateUtil::screenToSceneSpaceCoordinate(const float4x4 &transform, float2 coords)
{
    float2 mapped = {coords.x, 1 - coords.y};
    return (inverse(transform) * float4(mapped, 0, 1)).xy;
}

float2 CoordinateUtil::sceneToScreenSpaceCoordinate(const float4x4 &transform, float2 coords)
{
    auto transformed = (transform * float4(coords, 0, 1));
    return {transformed.x, 1 - transformed.y};
}
