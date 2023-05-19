#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test VertexRegion::cutWithVertices")
{
    std::vector<psdf::VertexRegion> input =
        psdf::TestUtils::readVertexRegionList("Data/Tests/point_cut_point_input.csv");
    psdf::VertexRegion::cutWithVertices(input, input);

    auto expectedResult = psdf::TestUtils::readVertexRegionList("Data/Tests/point_cut_point_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedResult, input));
}
