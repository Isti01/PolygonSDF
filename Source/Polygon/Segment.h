#pragma once

#include "Point.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Segment
{
  public:
    using Endpoints = std::array<Point, 2>;

    Segment(const Endpoints &endpoints);

    Endpoints getEndpoints() const;

  private:
    Endpoints mEndpoints;
};

} // namespace psdf
