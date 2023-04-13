#pragma once

#include "Point.h"
#include "Segment.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class SubPolygon
{
  public:
    using Points = std::vector<Point>;
    using Segments = std::vector<Segment>;

    using FloatPoints = std::vector<float2>;
    using FloatSegments = std::vector<std::array<float2, 2>>;

    SubPolygon(Points points);

    Points getPoints() const;
    Segments getSegments() const;

    FloatPoints getFloatPoints() const;
    FloatSegments getFloatSegments() const;

  private:
    static Segments connectOrderedPoints(const std::vector<Point> &points);

  private:
    Points mPoints;
    Segments mSegments;
};

} // namespace psdf
