#pragma once

#include <Falcor.h>
#include <sstream>
#include <string>
#include <vector>

#include "../../Source/Algorithm/Region/PointRegion.h"

namespace psdf
{
using namespace Falcor;

class TestUtils
{
    static constexpr int kMaxUlps = 30;
  public:
    static PointRegion readPointRegion(const std::string &spaceSeparatedList);
    static LineRegion readLineRegion(const std::string &spaceSeparatedList);

    static std::vector<glm::dvec2> readDouble2Vector(const std::string &spaceSeparatedList);

    static std::vector<psdf::PointRegion> readPointRegionList(const std::string &path);
    static std::vector<psdf::LineRegion> readLineRegionList(const std::string &path);

    static bool areDouble2VectorsEqual(const std::vector<glm::dvec2> &expected, const std::vector<glm::dvec2> &result,
                                       int maxUlps = kMaxUlps);

    static bool arePointRegionsEqual(const std::vector<PointRegion> &expected, const std::vector<PointRegion> &actual,
                                     int maxUlps = kMaxUlps);

  private:
    TestUtils() = default;
};

}; // namespace psdf
