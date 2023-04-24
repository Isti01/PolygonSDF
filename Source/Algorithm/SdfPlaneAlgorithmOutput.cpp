#include <fstream>
#include <json/json.hpp>

#include "SdfPlaneAlgorithmOutput.h"

using json = nlohmann::json;
using namespace psdf;

SdfPlaneAlgorithmOutput::SharedPtr SdfPlaneAlgorithmOutput::create(std::vector<PointRegion> pointRegions,
                                                                   std::vector<LineRegion> lineRegions)
{
    return SharedPtr(new SdfPlaneAlgorithmOutput(std::move(pointRegions), std::move(lineRegions)));
}

SdfPlaneAlgorithmOutput::SdfPlaneAlgorithmOutput(std::vector<PointRegion> pointRegions,
                                                 std::vector<LineRegion> lineRegions)
    : mPointRegions(std::move(pointRegions)), mLineRegions(std::move(lineRegions))
{
}

std::vector<PointRegion> SdfPlaneAlgorithmOutput::getPointRegions() const
{
    return mPointRegions;
}

std::vector<LineRegion> SdfPlaneAlgorithmOutput::getLineRegions() const
{
    return mLineRegions;
}

static json getPointJson(Point point)
{
    json json;
    json["x"] = point.x;
    json["y"] = point.y;
    return json;
}

static std::vector<json> getBoundsJson(const std::vector<Point> &bounds)
{
    std::vector<json> boundJson;

    for (const auto &point : bounds)
    {
        boundJson.emplace_back(getPointJson(point));
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
    for (const auto &pointRegion : mPointRegions)
    {
        json pointJson;
        pointJson["point"] = getPointJson(pointRegion.getPoint());
        pointJson["cornerSign"] = pointRegion.getCornerSign();
        pointJson["bounds"] = getBoundsJson(pointRegion.getBounds());
        vertices.emplace_back(std::move(pointJson));
    }

    std::vector<json> segments;
    for (const auto &lineRegion : mLineRegions)
    {
        json lineJson;
        lineJson["start"] = getPointJson(lineRegion.getSegment().getPoint1());
        lineJson["end"] = getPointJson(lineRegion.getSegment().getPoint2());
        lineJson["bounds"] = getBoundsJson(lineRegion.getBounds());
        segments.emplace_back(std::move(lineJson));
    }

    result["vertices"] = vertices;
    result["segments"] = segments;
    file << result.dump();

    return true;
}
