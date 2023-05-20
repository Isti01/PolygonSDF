#pragma once

#include <Falcor.h>
#include <sstream>
#include <string>
#include <vector>

#include "../../Source/Algorithm/Region/VertexRegion.h"
#include "../../Source/Shape/Shape.h"

namespace psdf
{
using namespace Falcor;

class TestUtils
{
    static constexpr double kEpsilon = 0.000001;

  public:
    static VertexRegion readVertexRegion(const std::string &spaceSeparatedList);
    static EdgeRegion readEdgeRegion(const std::string &spaceSeparatedList);

    static std::vector<glm::dvec2> readDouble2Vector(const std::string &spaceSeparatedList);

    static Shape::SharedPtr readShape(const std::string &path);
    static std::vector<psdf::VertexRegion> readVertexRegionList(const std::string &path);
    static std::vector<psdf::EdgeRegion> readEdgeRegionList(const std::string &path);

    static bool areDouble2VectorsEqual(const std::vector<glm::dvec2> &expected, const std::vector<glm::dvec2> &result,
                                       double epsilon = kEpsilon);

    static bool arePointRegionsEqual(const std::vector<VertexRegion> &expected, const std::vector<VertexRegion> &actual,
                                     double epsilon = kEpsilon);
    static bool areLineRegionsEqual(const std::vector<EdgeRegion> &expected, const std::vector<EdgeRegion> &actual,
                                    double epsilon = kEpsilon);

  private:
    TestUtils() = default;
};

}; // namespace psdf
