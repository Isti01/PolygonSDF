#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test EdgeRegion::cutWithEdges")
{
    auto inputLines = psdf::TestUtils::readEdgeRegionList("Data/Tests/line_cut_line_line_input.csv");
    psdf::EdgeRegion::cutWithEdges(inputLines, inputLines);

    auto expectedResult = psdf::TestUtils::readEdgeRegionList("Data/Tests/line_cut_line_line_output.csv");
    CHECK(psdf::TestUtils::areLineRegionsEqual(expectedResult, inputLines));
}
