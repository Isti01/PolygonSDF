#include "TestUtils.h"

using namespace psdf;
using namespace Falcor;

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
