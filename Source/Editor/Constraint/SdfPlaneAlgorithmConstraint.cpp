#include "SdfPlaneAlgorithmConstraint.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"

using namespace psdf;

SdfPlaneAlgorithmConstraint::SharedPtr SdfPlaneAlgorithmConstraint::create()
{
    return SharedPtr(new SdfPlaneAlgorithmConstraint());
}

bool isPolygonEligibleForAlgorithm(const Polygon::SharedPtr &pPolygon)
{
    const auto &segments = pPolygon->getSegments();
    const size_t segmentCount = segments.size();
    for (size_t i = 0; i < segmentCount; i++)
    {
        const auto &segment = segments[i];
        for (size_t j = 2; j < segmentCount - 1; j++) // we don't need to check neighboring segments
        {
            const size_t indexToCheck = (i + j) % segmentCount;
            if (segment.isIntersecting(segments[indexToCheck]))
            {
                return false;
            }
        }
    }

    return true;
}

bool SdfPlaneAlgorithmConstraint::evaluate(const EditorStack::SharedPtr &pStack,
                                           const EditorCommand::SharedPtr &pCommand)
{
    if (std::dynamic_pointer_cast<CalculateSdfPlaneAlgorithmCommand>(pCommand))
    {
        auto top = pStack->peek();
        if (!top || top->polygon->getAlgorithmOutput() != nullptr)
        {
            return false;
        }

        return isPolygonEligibleForAlgorithm(top->polygon);
    }
    return true;
}

std::string SdfPlaneAlgorithmConstraint::getName() const
{
    return "SdfPlaneAlgorithmConstraint";
}
