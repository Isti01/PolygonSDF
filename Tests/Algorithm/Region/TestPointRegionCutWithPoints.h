#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"


TEST_CASE("Test PointRegion::cutWithPoints")
{
    std::vector<psdf::PointRegion> input = psdf::TestUtils::readPointRegionList("Data/Tests/point_cut_point_input.csv");
    psdf::PointRegion::cutWithPoints(input);

    auto expectedResult = psdf::TestUtils::readPointRegionList("Data/Tests/point_cut_point_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedResult, input));
}
