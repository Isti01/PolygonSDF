#pragma once

#include "catch.hpp"

#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../Source/Algorithm/Region/Region.h"
#include "../../Source/Algorithm/SdfPlaneAlgorithm.h"
#include "../../Source/Polygon/Polygon.h"
#include "../Util/TestUtils.h"

TEST_CASE("Test SdfPlaneAlgorithm::calculateForPolygon")
{
    psdf::Polygon::SharedPtr input = psdf::TestUtils::readPolygon("Data/Tests/sdf_algorithm_polygon_input.csv");
    auto result = psdf::SdfPlaneAlgorithm::calculateForPolygon(input);

    auto expectedPoints = psdf::TestUtils::readPointRegionList("Data/Tests/sdf_algorithm_point_region_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedPoints, result->getPointRegions()));

    auto expectedLines = psdf::TestUtils::readLineRegionList("Data/Tests/sdf_algorithm_line_region_output.csv");
    CHECK(psdf::TestUtils::areLineRegionsEqual(expectedLines, result->getLineRegions()));
}
