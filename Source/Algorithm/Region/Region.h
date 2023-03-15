#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Region
{
  public:
    static constexpr float InitialBoundScale = 1e13f;

  protected:
    Region();

  protected:
    rmcv::mat4x2 mBounds;
};

} // namespace psdf
