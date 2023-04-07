#pragma once

#include <Falcor.h>
#include <sstream>
#include <string>
#include <vector>

#include "../../Source/Algorithm/Region/PointRegion.h"
#include "../../Source/Polygon/Polygon.h"

namespace psdf
{
using namespace Falcor;

class TestUtils
{
    static constexpr double kEpsilon = 0.000001;

  public:
    static PointRegion readPointRegion(const std::string &spaceSeparatedList);
    static LineRegion readLineRegion(const std::string &spaceSeparatedList);

    static std::vector<glm::dvec2> readDouble2Vector(const std::string &spaceSeparatedList);

    static Polygon::SharedPtr readPolygon(const std::string& path);
    static std::vector<psdf::PointRegion> readPointRegionList(const std::string &path);
    static std::vector<psdf::LineRegion> readLineRegionList(const std::string &path);

    static bool areDouble2VectorsEqual(const std::vector<glm::dvec2> &expected, const std::vector<glm::dvec2> &result,
                                       double epsilon = kEpsilon);

    static bool arePointRegionsEqual(const std::vector<PointRegion> &expected, const std::vector<PointRegion> &actual,
                                     double epsilon = kEpsilon);
    static bool areLineRegionsEqual(const std::vector<LineRegion> &expected, const std::vector<LineRegion> &actual,
                                    double epsilon = kEpsilon);

  private:
    TestUtils() = default;
};

}; // namespace psdf
