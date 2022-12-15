#pragma once

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Point
{
  public:
    Point(float2 coordinates);

    float2 getCoordinates() const;

  private:
    float2 mCoordinates;
};

} // namespace psdf
