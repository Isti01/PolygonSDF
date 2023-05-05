#pragma once

namespace psdf
{

struct SdfPlaneAlgorithmExecutionDesc
{
    bool reorderPoints;
    size_t pointRegionSubdivision;
    double initialBoundScale;
};

static constexpr SdfPlaneAlgorithmExecutionDesc kDefaultSdfPlaneAlgorithmExecutionDesc{true, 5, 1e7};

} // namespace psdf
