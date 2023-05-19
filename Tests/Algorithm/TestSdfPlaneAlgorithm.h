#pragma once

#include "catch.hpp"

#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../Source/Algorithm/Region/Region.h"
#include "../../Source/Algorithm/SdfPlaneAlgorithm.h"
#include "../../Source/Algorithm/SdfPlaneAlgorithmExecutionDesc.h"
#include "../../Source/Polygon/Shape.h"
#include "../Util/TestUtils.h"

TEST_CASE("Test SdfPlaneAlgorithm::calculateForShape")
{
    psdf::SdfPlaneAlgorithmExecutionDesc desc = psdf::kDefaultSdfPlaneAlgorithmExecutionDesc;
    desc.reorderPoints = false;
    psdf::Shape::SharedPtr input = psdf::TestUtils::readShape("Data/Tests/sdf_algorithm_polygon_input.csv");
    auto result = psdf::SdfPlaneAlgorithm::calculateForShape(input, desc);

    auto expectedPoints = psdf::TestUtils::readVertexRegionList("Data/Tests/sdf_algorithm_point_region_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedPoints, result->getVertexRegions()));

    auto expectedLines = psdf::TestUtils::readEdgeRegionList("Data/Tests/sdf_algorithm_line_region_output.csv");
    CHECK(psdf::TestUtils::areLineRegionsEqual(expectedLines, result->getEdgeRegions()));
}
