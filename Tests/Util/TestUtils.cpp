#include <fstream>

#include "TestUtils.h"

using namespace psdf;
using namespace Falcor;

VertexRegion TestUtils::readVertexRegion(const std::string &spaceSeparatedList)
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

    return {bounds, point, sign, 5};
}

EdgeRegion TestUtils::readEdgeRegion(const std::string &spaceSeparatedList)
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

    return {bounds, Edge{{point1, point2}}};
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

Shape::SharedPtr TestUtils::readShape(const std::string &path)
{
    std::vector<Vertex> points;
    std::ifstream f(path);
    Vertex current;
    while (f >> current.x >> current.y)
    {
        points.push_back(current);
    }

    return Shape::create({points});
}

std::vector<psdf::VertexRegion> TestUtils::readVertexRegionList(const std::string &path)
{
    std::vector<psdf::VertexRegion> vertexRegions;
    std::ifstream f(path);
    for (std::string line; std::getline(f, line);)
    {
        vertexRegions.push_back(psdf::TestUtils::readVertexRegion(line));
    }
    return vertexRegions;
}

std::vector<psdf::EdgeRegion> TestUtils::readEdgeRegionList(const std::string &path)
{
    std::vector<psdf::EdgeRegion> edgeRegions;
    std::ifstream f(path);
    for (std::string line; std::getline(f, line);)
    {
        edgeRegions.push_back(psdf::TestUtils::readEdgeRegion(line));
    }
    return edgeRegions;
}

bool TestUtils::areDouble2VectorsEqual(const std::vector<glm::dvec2> &expected, const std::vector<glm::dvec2> &result,
                                       double epsilon)
{

    if (expected.size() != result.size())
    {
        return false;
    }

    for (size_t i = 0; i < expected.size(); i++)
    {
        if (!glm::all(glm::epsilonEqual(expected[i], result[i], epsilon)))
        {
            return false;
        }
    }
    return true;
}

bool TestUtils::arePointRegionsEqual(const std::vector<VertexRegion> &expected, const std::vector<VertexRegion> &actual,
                                     double epsilon)
{
    if (expected.size() != actual.size())
    {
        return false;
    }

    for (size_t i = 0; i < expected.size(); i++)
    {
        if (!areDouble2VectorsEqual(expected[i].getBounds(), actual[i].getBounds(), epsilon))
        {
            return false;
        }
        if (glm::abs(expected[i].getCornerSign() - actual[i].getCornerSign()) > epsilon)
        {
            return false;
        }
        if (!glm::all(glm::epsilonEqual(expected[i].getVertex(), actual[i].getVertex(), epsilon)))
        {
            return false;
        }
    }

    return true;
}

bool TestUtils::areLineRegionsEqual(const std::vector<EdgeRegion> &expected, const std::vector<EdgeRegion> &actual,
                                    double epsilon)
{
    if (expected.size() != actual.size())
    {
        return false;
    }

    for (size_t i = 0; i < expected.size(); i++)
    {
        if (!areDouble2VectorsEqual(expected[i].getBounds(), actual[i].getBounds(), epsilon))
        {
            return false;
        }
        auto expectedSegment = expected[i].getEdge();
        auto actualSegment = actual[i].getEdge();
        if (!glm::all(glm::epsilonEqual(expectedSegment.getVertex1(), actualSegment.getVertex1(), epsilon)))
        {
            return false;
        }
        if (!glm::all(glm::epsilonEqual(expectedSegment.getVertex2(), actualSegment.getVertex2(), epsilon)))
        {
            return false;
        }
    }

    return true;
}
