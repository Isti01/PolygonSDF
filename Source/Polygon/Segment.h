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

    Point getPoint1() const;
    Point getPoint2() const;

    glm::dvec2 getEdgeVector() const;
    bool isIntersecting(const Segment& other) const;

  private:
    Endpoints mEndpoints;
};

} // namespace psdf
