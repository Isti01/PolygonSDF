#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

struct VertexRegionBoundVertex
{
    float2 vertex;
    float2 position;
    float signedDistance;
};

} // namespace psdf
