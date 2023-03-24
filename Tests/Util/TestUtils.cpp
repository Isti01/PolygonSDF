#include <fstream>

#include "TestUtils.h"

using namespace psdf;
using namespace Falcor;

PointRegion TestUtils::readPointRegion(const std::string &spaceSeparatedList)
{
    std::stringstream ss(spaceSeparatedList);
    glm::dvec2 point;
    ss >> point[0] >> point[1];

    double sign;
    ss >> sign;

    std::vector<glm::dvec2> bounds;
    glm::dvec2 bound;
    while (ss >> bound[0] >> bound[1])
    {
        bounds.push_back(bound);
    }

    return {bounds, point, sign};
}

LineRegion TestUtils::readLineRegion(const std::string &spaceSeparatedList)
{
    std::stringstream ss(spaceSeparatedList);
    glm::dvec2 point1;
    glm::dvec2 point2;
    ss >> point1[0] >> point1[1] >> point2[0] >> point2[1];

    std::vector<glm::dvec2> bounds;
    glm::dvec2 bound;
    while (ss >> bound[0] >> bound[1])
    {
        bounds.push_back(bound);
    }

    return {bounds, Segment{{point1, point2}}};
}

std::vector<glm::dvec2> TestUtils::readDouble2Vector(const std::string &spaceSeparatedList)
{
    std::stringstream ss(spaceSeparatedList);
    std::vector<glm::dvec2> result;
    glm::dvec2 value;

    while (ss >> value[0] >> value[1])
    {
        result.push_back(value);
    }
    return result;
}

std::vector<psdf::PointRegion> TestUtils::readPointRegionList(const std::string &path)
{
    std::vector<psdf::PointRegion> pointRegions;
    std::ifstream f(path);
    for (std::string line; std::getline(f, line);)
    {
        pointRegions.push_back(psdf::TestUtils::readPointRegion(line));
    }
    return pointRegions;
}

std::vector<psdf::LineRegion> TestUtils::readLineRegionList(const std::string &path)
{
    std::vector<psdf::LineRegion> lineRegions;
    std::ifstream f(path);
    for (std::string line; std::getline(f, line);)
    {
        lineRegions.push_back(psdf::TestUtils::readLineRegion(line));
    }
    return lineRegions;
}

bool TestUtils::areDouble2VectorsEqual(const std::vector<glm::dvec2> &expected, const std::vector<glm::dvec2> &result,
                                       int maxUlps)
{

    if (expected.size() != result.size())
    {
        return false;
    }

    for (size_t i = 0; i < expected.size(); i++)
    {
        if (!glm::all(glm::equal(expected[i], result[i], maxUlps)))
        {
            return false;
        }
    }
    return true;
}

bool TestUtils::arePointRegionsEqual(const std::vector<PointRegion> &expected, const std::vector<PointRegion> &actual,
                                     int maxUlps)
{
    if (expected.size() != actual.size())
    {
        return false;
    }

    for (size_t i = 0; i < expected.size(); i++)
    {
        if (!areDouble2VectorsEqual(expected[i].getBounds(), actual[i].getBounds()))
        {
            return false;
        }
        if (expected[i].getCornerSign() != actual[i].getCornerSign())
        {
            return false;
        }
        if (!glm::all(glm::equal(expected[i].getPoint(), actual[i].getPoint(), maxUlps)))
        {
            return false;
        }
    }

    return true;
}
