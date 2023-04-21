#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test LineRegion::cutWithLines")
{
    auto inputLines = psdf::TestUtils::readLineRegionList("Data/Tests/line_cut_line_line_input.csv");
    psdf::LineRegion::cutWithLines(inputLines, inputLines);

    auto expectedResult = psdf::TestUtils::readLineRegionList("Data/Tests/line_cut_line_line_output.csv");
    CHECK(psdf::TestUtils::areLineRegionsEqual(expectedResult, inputLines));
}
