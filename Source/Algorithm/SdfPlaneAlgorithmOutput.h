#pragma once

#include "Region/LineRegion.h"
#include "Region/PointRegion.h"

#include <vector>

namespace psdf
{

struct SdfPlaneAlgorithmOutput
{
    std::vector<PointRegion> pointRegions;
    std::vector<LineRegion> lineRegions;
};

} // namespace psdf
