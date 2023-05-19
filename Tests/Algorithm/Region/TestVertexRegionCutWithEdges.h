#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

TEST_CASE("Test VertexRegion::cutWithEdges")
{
    auto inputPoints = psdf::TestUtils::readVertexRegionList("Data/Tests/point_cut_line_points_input.csv");
    auto inputLines = psdf::TestUtils::readEdgeRegionList("Data/Tests/point_cut_line_Lines_input.csv");
    psdf::VertexRegion::cutWithEdges(inputPoints, inputLines);

    auto expectedResult = psdf::TestUtils::readVertexRegionList("Data/Tests/point_cut_line_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedResult, inputPoints));
}
