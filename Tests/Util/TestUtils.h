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
  public:
    static PointRegion readPointRegion(const std::string &spaceSeparatedList);

    static std::vector<glm::dvec2> readDouble2Vector(const std::string &spaceSeparatedList);

    static bool areDouble2VectorsEqual(const std::vector<glm::dvec2> &expected, const std::vector<glm::dvec2> &result,
                                       int maxUlps = 10);

    static bool arePointRegionsEqual(const std::vector<PointRegion> &expected, const std::vector<PointRegion> &actual,
                                     int maxUlps = 10);

  private:
    TestUtils() = default;
};

}; // namespace psdf
