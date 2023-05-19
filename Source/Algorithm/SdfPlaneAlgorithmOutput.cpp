#include <fstream>
#include <json/json.hpp>

#include "SdfPlaneAlgorithmOutput.h"

using json = nlohmann::json;
using namespace psdf;

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithmOutput::create(std::vector<VertexRegion> vertexRegions,
                                                                   std::vector<EdgeRegion> edgeRegions)
{
    return SharedPtr(new SdfPlaneAlgorithmOutput(std::move(vertexRegions), std::move(edgeRegions)));
}

SdfPlaneAlgorithmOutput::SdfPlaneAlgorithmOutput(std::vector<VertexRegion> vertexRegions,
                                                 std::vector<EdgeRegion> edgeRegions)
    : mVertexRegions(std::move(vertexRegions)), mEdgeRegions(std::move(edgeRegions))
{
}

std::vector<VertexRegion> SdfPlaneAlgorithmOutput::getVertexRegions() const
{
    return mVertexRegions;
}

std::vector<EdgeRegion> SdfPlaneAlgorithmOutput::getEdgeRegions() const
{
    return mEdgeRegions;
}

static json getVertexJson(Vertex vertex)
{
    json json;
    json["x"] = vertex.x;
    json["y"] = vertex.y;
    return json;
}

static std::vector<json> getBoundsJson(const std::vector<Vertex> &bounds)
{
    std::vector<json> boundJson;

    for (const auto &vertex : bounds)
    {
        boundJson.emplace_back(getVertexJson(vertex));
    }

    return boundJson;
}

bool SdfPlaneAlgorithmOutput::saveJson(const std::string &path) const
{
    std::ofstream file(path);
    if (!file)
    {
        return false;
    }

    json result;

    std::vector<json> vertices;
    for (const auto &vertexRegion : mVertexRegions)
    {
        json vertexJson;
        vertexJson["vertex"] = getVertexJson(vertexRegion.getVertex());
        vertexJson["cornerSign"] = vertexRegion.getCornerSign();
        vertexJson["bounds"] = getBoundsJson(vertexRegion.getBounds());
        vertices.emplace_back(std::move(vertexJson));
    }

    std::vector<json> edges;
    for (const auto &edgeRegion : mEdgeRegions)
    {
        json lineJson;
        lineJson["start"] = getVertexJson(edgeRegion.getEdge().getVertex1());
        lineJson["end"] = getVertexJson(edgeRegion.getEdge().getVertex2());
        lineJson["bounds"] = getBoundsJson(edgeRegion.getBounds());
        edges.emplace_back(std::move(lineJson));
    }

    result["vertexRegions"] = vertices;
    result["edgeRegions"] = edges;
    file << result.dump();

    return true;
}
