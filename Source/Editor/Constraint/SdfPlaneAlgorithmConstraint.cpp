#include "SdfPlaneAlgorithmConstraint.h"
#include "../Command/CalculateSdfPlaneAlgorithmCommand.h"

using namespace psdf;

SdfPlaneAlgorithmConstraint::SharedPtr SdfPlaneAlgorithmConstraint::create()
{
    return SharedPtr(new SdfPlaneAlgorithmConstraint());
}

static bool isSegmentIntersectingPolygonOutline(const Edge &edge, const Outline &outline)
{
    for (const auto &otherSegment : outline.getEdges())
    {
        if (edge.isIntersecting(otherSegment))
        {
            return true;
        }
    }

    return false;
}

static bool isPolygonEligibleForAlgorithm(const Shape::SharedPtr &pShaper)
{
    const auto &outlines = pShaper->getOutlines();
    const size_t outlineCount = outlines.size();
    for (size_t i = 0; i < outlineCount; i++)
    {
        const auto &outline = outlines[i];
        const auto &currentEdges = outline.getEdges();
        const auto edgeCount = currentEdges.size();

        for (size_t j = 0; j < edgeCount; j++)
        {
            const auto &edge = currentEdges[j];

            for (size_t eInd = 2; eInd < edgeCount - 1; eInd++) // we don't need to check neighboring segments
            {
                const size_t indexToCheck = (j + eInd) % edgeCount;
                if (edge.isIntersecting(currentEdges[indexToCheck]))
                {
                    return false;
                }
            }

            for (size_t k = 0; k < outlines.size(); k++)
            {
                if (i == k)
                {
                    continue;
                }
                if (isSegmentIntersectingPolygonOutline(edge, outlines[k]))
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

        return isPolygonEligibleForAlgorithm(top->pShape);
    }
    return true;
}

std::string SdfPlaneAlgorithmConstraint::getName() const
{
    return "SdfPlaneAlgorithmConstraint";
}
