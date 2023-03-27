#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test LineRegion::cutWithPoints")
{
    auto inputPoints = psdf::TestUtils::readPointRegionList("Data/Tests/line_cut_point_point_input.csv");
    auto inputLines = psdf::TestUtils::readLineRegionList("Data/Tests/line_cut_point_line_input.csv");
    psdf::LineRegion::cutWithPoints(inputLines, inputPoints);

    auto expectedResult = psdf::TestUtils::readLineRegionList("Data/Tests/line_cut_point_line_output.csv");
    CHECK(psdf::TestUtils::areLineRegionsEqual(expectedResult, inputLines));
}
