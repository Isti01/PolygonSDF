#include "CoordinateUtil.h"

using namespace psdf;
using namespace Falcor;

float2 CoordinateUtil::screenToSceneSpaceCoordinate(const float4x4 &transform, float2 coords)
{
    float2 mapped = float2(coords.x, coords.y) * 2.0f - 1.0f;
    return (inverse(transform) * float4(mapped.x, -mapped.y, 0, 1)).xy;
}

float2 CoordinateUtil::sceneToScreenSpaceCoordinate(const float4x4 &transform, float2 coords)
{
    auto transformed = (transform * float4(coords, 0, 1));
    return float2(transformed.x, -transformed.y) / 2.0f + 0.5f;
}

std::optional<size_t> CoordinateUtil::findClosestInSubPolygon(const Polygon::Points &points, Point point)
{
    auto isPointCloser = [point](const Point &p1, const Point &p2) {
        return glm::distance(point, p1) < glm::distance(point, p2);
    };
    auto iterator = std::min_element(points.begin(), points.end(), isPointCloser);
    if (iterator == points.end())
    {
        return std::nullopt;
    }

    return iterator - points.begin();
}

std::optional<std::pair<size_t, size_t>> CoordinateUtil::findClosestPointIndex(const std::vector<SubPolygon> &polygons,
                                                                               Point point)
{
    std::optional<std::pair<size_t, size_t>> result = std::nullopt;
    for (size_t i = 0; i < polygons.size(); i++)
    {
        const auto &polygon = polygons[i];
        auto closest = findClosestInSubPolygon(polygon.getPoints(), point);
        if (!closest)
        {
            continue;
        }
        if (!result || glm::distance(polygons[i].getPoints()[*closest], point) <
                           glm::distance(polygons[result->first].getPoints()[result->second], point))
        {
            result = {i, *closest};
        }
    }
    return result;
}
