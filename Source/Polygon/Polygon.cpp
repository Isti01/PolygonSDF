#include "Polygon.h"
#include "../Algorithm/SdfPlaneAlgorithm.h"

#include <fstream>
#include <json/json.hpp>
#include <utility>

using json = nlohmann::json;
using namespace psdf;

Polygon::SharedPtr Polygon::kExamplePolygon = Polygon::create({
    Points{{.5, 0}, {0, .5}, {-.5, 0}, {0, -.5}},
    Points{{.75, 0}, {0, -.75}, {-.75, 0}, {0, .75}},
    Points{{1.25, 0}, {0, -1.25}, {-1.25, 0}, {0, 1.25}},
});

Polygon::SharedPtr Polygon::kSquarePolygon = Polygon::create({
    Points{{1, 0}, {0, -1}, {-1, 0}, {0, 1}},
});

Polygon::SharedPtr Polygon::create(std::vector<SubPolygon> polygons)
{
    return SharedPtr(new Polygon(std::move(polygons)));
}

Polygon::Polygon(std::vector<SubPolygon> polygons) : mPolygons(std::move(polygons))
{
}

std::vector<SubPolygon> Polygon::getPolygons() const
{
    return mPolygons;
}

Polygon::FloatSegments Polygon::getAllFloatSegments() const
{
    FloatSegments floatSegments;
    for (const auto &mPolygon : mPolygons)
    {
        const auto &subSegments = mPolygon.getFloatSegments();
        std::copy(subSegments.cbegin(), subSegments.cend(), std::back_inserter(floatSegments));
    }
    return floatSegments;
}
Polygon::Segments Polygon::getAllSegments() const
{
    Segments segments;
    for (const auto &mPolygon : mPolygons)
    {
        const auto &subSegments = mPolygon.getSegments();
        std::copy(subSegments.cbegin(), subSegments.cend(), std::back_inserter(segments));
    }

    return segments;
}
SdfPlaneAlgorithmOutput::SharedPtr Polygon::getAlgorithmOutput() const
{
    return mpSdfPlaneAlgorithmOutput;
}

void Polygon::runAlgorithm()
{
    mpSdfPlaneAlgorithmOutput = SdfPlaneAlgorithm::calculateForPolygon(this->shared_from_this());
}

Polygon::SharedPtr Polygon::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if (!file)
    {
        return nullptr;
    }
    auto content = json::parse(file, nullptr, false);
    if (!content.contains("groups"))
    {
        return nullptr;
    }
    auto groups = content["groups"];
    if (!groups.is_array())
    {
        return nullptr;
    }

    std::vector<SubPolygon> polygons;
    std::vector<Point> groupVertices;

    for (const auto &group : groups)
    {
        if (!group.is_array())
        {
            return nullptr;
        }
        for (const auto &vertex : group)
        {
            if (!vertex.contains("x") || !vertex.contains("y") || !vertex["x"].is_number() || !vertex["y"].is_number())
            {
                return nullptr;
            }
            Point p{vertex["x"], vertex["y"]};
            groupVertices.emplace_back(p);
        }
        if (!groupVertices.empty())
        {
            polygons.emplace_back(groupVertices);
            groupVertices.clear();
        }
    }
    return polygons.empty() ? nullptr : create(polygons);
}
