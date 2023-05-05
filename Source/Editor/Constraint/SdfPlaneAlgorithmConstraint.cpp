#include "SdfPlaneAlgorithmConstraint.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"

using namespace psdf;

SdfPlaneAlgorithmConstraint::SharedPtr SdfPlaneAlgorithmConstraint::create()
{
    return SharedPtr(new SdfPlaneAlgorithmConstraint());
}

static bool isSegmentIntersectingPolygonOutline(const Segment &segment, const SubPolygon &subPolygon)
{
    for (const auto &otherSegment : subPolygon.getSegments())
    {
        if (segment.isIntersecting(otherSegment))
        {
            return true;
        }
    }

    return false;
}

static bool isPolygonEligibleForAlgorithm(const Polygon::SharedPtr &pPolygon)
{
    const auto &polygons = pPolygon->getPolygons();
    const size_t polygonCount = polygons.size();
    for (size_t i = 0; i < polygonCount; i++)
    {
        const auto &polygon = polygons[i];
        const auto &currentSegments = polygon.getSegments();
        const auto currentSegmentCount = currentSegments.size();

        for (size_t j = 0; j < currentSegmentCount; j++)
        {
            const auto &segment = currentSegments[j];

            for (size_t sInd = 2; sInd < currentSegmentCount - 1; sInd++) // we don't need to check neighboring segments
            {
                const size_t indexToCheck = (j + sInd) % currentSegmentCount;
                if (segment.isIntersecting(currentSegments[indexToCheck]))
                {
                    return false;
                }
            }

            for (size_t k = 0; k < polygons.size(); k++)
            {
                if (i == k)
                {
                    continue;
                }
                if (isSegmentIntersectingPolygonOutline(segment, polygons[k]))
                {
                    return false;
                }
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
        if (!top)
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
