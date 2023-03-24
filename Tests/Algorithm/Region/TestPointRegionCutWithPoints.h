#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

std::vector<psdf::PointRegion> readTestData(const std::string &path)
{
    std::vector<psdf::PointRegion> pointRegions;
    std::ifstream f(path);
    for (std::string line; std::getline(f, line);)
    {
        pointRegions.push_back(psdf::TestUtils::readPointRegion(line));
    }
    return pointRegions;
}

TEST_CASE("Test PointRegion::cutWithPoints")
{
    std::vector<psdf::PointRegion> input = readTestData("Data/Tests/point_cut_point_input.csv");
    psdf::PointRegion::cutWithPoints(input);

    auto expectedResult = readTestData("Data/Tests/point_cut_point_output.csv");
    CHECK(psdf::TestUtils::arePointRegionsEqual(expectedResult, input));
}
