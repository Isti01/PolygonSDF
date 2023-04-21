#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

struct PointRegionBoundVertex
{
    float2 point;
    float2 position;
    float signedDistance;
};

} // namespace psdf
