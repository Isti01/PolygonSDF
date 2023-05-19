#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test EdgeRegion::cutWithVertices")
{
    auto inputPoints = psdf::TestUtils::readVertexRegionList("Data/Tests/line_cut_point_point_input.csv");
    auto inputLines = psdf::TestUtils::readEdgeRegionList("Data/Tests/line_cut_point_line_input.csv");
    psdf::EdgeRegion::cutWithVertices(inputLines, inputPoints);

    auto expectedResult = psdf::TestUtils::readEdgeRegionList("Data/Tests/line_cut_point_line_output.csv");
    CHECK(psdf::TestUtils::areLineRegionsEqual(expectedResult, inputLines));
}
