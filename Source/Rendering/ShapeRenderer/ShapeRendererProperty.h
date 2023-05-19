#pragma once

#include "Utils/Math/Vector.h"
#include <string>
#include <variant>

namespace psdf
{
using namespace Falcor;

struct ShapeRendererProperty
{
    std::string key;
    std::variant<float3, size_t, float, bool> value;
};

} // namespace psdf
