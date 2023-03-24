#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test PointRegion::cutWithLines")
{
    auto inputPoints = psdf::TestUtils::readPointRegionList("Data/Tests/point_cut_line_points_input.csv");
    auto inputLines = psdf::TestUtils::readLineRegionList("Data/Tests/point_cut_line_Lines_input.csv");
    psdf::PointRegion::cutWithLines(inputPoints, inputLines);

    auto expectedResult = psdf::TestUtils::readPointRegionList("Data/Tests/point_cut_line_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedResult, inputPoints));
}
