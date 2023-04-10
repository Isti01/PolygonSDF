#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

struct RegionBoundVertex
{
    float2 position;
    float signedDistance;
};

} // namespace psdf
