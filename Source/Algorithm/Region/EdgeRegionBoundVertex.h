#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

struct EdgeRegionBoundVertex
{
    float2 position;
    float signedDistance;
};

} // namespace psdf
