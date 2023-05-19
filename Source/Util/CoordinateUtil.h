#pragma once

#include "../Polygon/Outline.h"
#include "../Polygon/Shape.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class CoordinateUtil
{
  public:
    static float2 screenToSceneSpaceCoordinate(const float4x4 &transform, float2 coords);
    static float2 sceneToScreenSpaceCoordinate(const float4x4 &transform, float2 coords);
    static std::optional<size_t> findClosestInOutline(const Shape::Vertices &points, Vertex point);
    static std::optional<std::pair<size_t, size_t>> findClosestPointIndex(const std::vector<Outline> &polygons,
                                                                          Vertex point);

  private:
    CoordinateUtil() = default;
};

} // namespace psdf
