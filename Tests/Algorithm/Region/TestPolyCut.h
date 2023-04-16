#pragma once

#include "catch.hpp"
#include <Falcor.h>
#include <fstream>
#include <sstream>
#include <string>

#include "../../../Source/Algorithm/Region/Region.h"
#include "../../Util/TestUtils.h"

struct RegionTestcase
{
    std::vector<glm::dvec2> startBounds;
    std::vector<glm::dvec2> points;
    std::vector<glm::dvec2> edgeVectors;
    std::vector<glm::dvec2> expectedBounds;
};

RegionTestcase readTestCase(const std::string &line)
{
    RegionTestcase testCase;

    std::stringstream ss(line);
    std::string part;

    std::getline(ss, part, ',');
    testCase.points = psdf::TestUtils::readDouble2Vector(part);

    std::getline(ss, part, ',');
    testCase.edgeVectors = psdf::TestUtils::readDouble2Vector(part);

    std::getline(ss, part, ',');
    testCase.startBounds = psdf::TestUtils::readDouble2Vector(part);

    std::getline(ss, part, ',');
    testCase.expectedBounds = psdf::TestUtils::readDouble2Vector(part);

    return testCase;
}

TEST_CASE("Test 1 Region::polyCut")
{
    std::ifstream f("Data/Tests/polycut_data.csv");
    for (std::string line; std::getline(f, line);)
    {
        RegionTestcase testCase = readTestCase(line);
        psdf::PointRegion region(testCase.startBounds, {0, 0}, 0);
        region.polyCut(testCase.points, testCase.edgeVectors);
        CHECK(psdf::TestUtils::areDouble2VectorsEqual(testCase.expectedBounds, region.getBounds()));
    }
}

TEST_CASE("Test 2 Region::polyCut")
{
    std::ifstream f("Data/Tests/nested_polygon_polycut_data.csv");
    for (std::string line; std::getline(f, line);)
    {
        RegionTestcase testCase = readTestCase(line);
        psdf::PointRegion region(testCase.startBounds, {0, 0}, 0);
        region.polyCut(testCase.points, testCase.edgeVectors);
        CHECK(psdf::TestUtils::areDouble2VectorsEqual(testCase.expectedBounds, region.getBounds()));
    }
}

