#include "Shape.h"
#include "../Algorithm/SdfPlaneAlgorithm.h"

#include <fstream>
#include <json/json.hpp>
#include <utility>

using json = nlohmann::json;
using namespace psdf;

Shape::SharedPtr Shape::kStarterShape = Shape::create({
    Vertices{{.5, 0}, {0, .5}, {-.5, 0}, {0, -.5}},
    Vertices{{.75, 0}, {0, -.75}, {-.75, 0}, {0, .75}},
    Vertices{{1.25, 0}, {0, -1.25}, {-1.25, 0}, {0, 1.25}},
});

Shape::SharedPtr Shape::kSquareShape = Shape::create({
    Vertices{{1, 0}, {0, -1}, {-1, 0}, {0, 1}},
});

Shape::SharedPtr Shape::create(std::vector<Outline> outlines)
{
    return SharedPtr(new Shape(std::move(outlines)));
}

Shape::Shape(std::vector<Outline> outlines) : mOutlines(std::move(outlines))
{
}

Vertex Shape::getCenter() const
{
    Vertex average{0};
    const auto &outlines = getOutlines();
    double pointWeight = std::accumulate(outlines.cbegin(), outlines.cend(), 0.0,
                                         [](double count, const auto &p) { return count + p.getVertices().size(); });
    for (const auto &outline : outlines)
    {
        for (const auto &vertex : outline.getVertices())
        {
            average += vertex / pointWeight;
        }
    }
    return average;
}

std::vector<Outline> Shape::getOutlines() const
{
    return mOutlines;
}
Shape::FloatEdges Shape::getAllFloatEdges() const
{
    FloatEdges floatEdges;
    for (const auto &outline : mOutlines)
    {
        const auto &edges = outline.getFloatEdges();
        std::copy(edges.cbegin(), edges.cend(), std::back_inserter(floatEdges));
    }
    return floatEdges;
}
Shape::Edges Shape::getAllEdges() const
{
    Edges allEdges;
    for (const auto &outline : mOutlines)
    {
        const auto &edges = outline.getEdges();
        std::copy(edges.cbegin(), edges.cend(), std::back_inserter(allEdges));
    }

    return allEdges;
}

SdfPlaneAlgorithmOutput::SharedPtr Shape::getAlgorithmOutput() const
{
    return mpSdfPlaneAlgorithmOutput;
}

void Shape::runAlgorithm(SdfPlaneAlgorithmExecutionDesc desc)
{
    mpSdfPlaneAlgorithmOutput = SdfPlaneAlgorithm::calculateForShape(this->shared_from_this(), desc);
}

Shape::SharedPtr Shape::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if (!file)
    {
        return nullptr;
    }
    auto content = json::parse(file, nullptr, false);
    if (!content.contains("outlines"))
    {
        return nullptr;
    }
    auto outlinesJson = content["outlines"];
    if (!outlinesJson.is_array())
    {
        return nullptr;
    }

    std::vector<Outline> outlines;
    std::vector<Vertex> groupVertices;

    for (const auto &outline : outlinesJson)
    {
        if (!outline.is_array())
        {
            return nullptr;
        }
        for (const auto &vertex : outline)
        {
            if (!vertex.contains("x") || !vertex.contains("y") || !vertex["x"].is_number() || !vertex["y"].is_number())
            {
                return nullptr;
            }
            Vertex p{vertex["x"], vertex["y"]};
            groupVertices.emplace_back(p);
        }
        if (!groupVertices.empty())
        {
            outlines.emplace_back(groupVertices);
            groupVertices.clear();
        }
    }
    return outlines.empty() ? nullptr : create(outlines);
}

bool Shape::saveJson(const std::string &path) const
{
    std::ofstream file(path);
    if (!file)
    {
        return false;
    }

    json result;
    std::vector<json> outlines;
    for (const auto &outline : mOutlines)
    {
        std::vector<json> groupJson;
        for (const auto &vertex : outline.getVertices())
        {
            json pointJson;
            pointJson["x"] = vertex.x;
            pointJson["y"] = vertex.y;
            groupJson.emplace_back(std::move(pointJson));
        }
        outlines.emplace_back(std::move(groupJson));
    }

    result["outlines"] = outlines;
    file << result.dump();

    return true;
}

double psdf::Shape::getCircumscribedCircleRadiusFromCenter() const
{
    glm::dvec2 origin = getCenter();
    double maxDistance = glm::distance(origin, mOutlines[0].getVertices()[0]);
    for (const auto &outline : mOutlines)
    {
        for (const auto &vertex : outline.getVertices())
        {
            maxDistance = glm::max(maxDistance, glm::distance(origin, vertex));
        }
    }
    return glm::abs(maxDistance);
}
