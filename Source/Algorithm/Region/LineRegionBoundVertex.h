#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

struct LineRegionBoundVertex
{
    float2 position;
    float signedDistance;
};

} // namespace psdf
