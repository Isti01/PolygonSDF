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

float2 CoordinateUtil::screenToSceneSpaceVector(const float4x4 &transform, float2 vector)
{
    return (transpose(inverse(transform)) * float4(vector, 0, 1)).xy;
}

std::optional<size_t> CoordinateUtil::findClosestPointIndex(const Polygon::Points &points, float2 point)
{
    auto isPointCloser = [point](const Point &p1, const Point &p2) {
        return glm::distance(point, p1.getCoordinates()) < glm::distance(point, p2.getCoordinates());
    };
    auto iterator = std::min_element(points.begin(), points.end(), isPointCloser);
    if (iterator == points.end())
    {
        return std::nullopt;
    }

    return iterator - points.begin();
}
