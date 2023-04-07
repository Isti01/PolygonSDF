#pragma once

#include "Point.h"
#include "Segment.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Polygon
{
  public:
    using Points = std::vector<Point>;
    using Segments = std::vector<Segment>;

    using FloatPoints = std::vector<float2>;
    using FloatSegments = std::vector<std::array<float2, 2>>;

    using SharedPtr = std::shared_ptr<Polygon>;

    static SharedPtr create(const std::vector<Point> &points);

    Points getPoints() const;
    Segments getSegments() const;

    FloatPoints getFloatPoints() const;
    FloatSegments getFloatSegments() const;

  private:
    Polygon(Points points, Segments segments);

    static Segments connectOrderedPoints(const std::vector<Point> &points);

  public:
    static Polygon::SharedPtr kExamplePolygon;

  private:
    Points mPoints;
    Segments mSegments;

};

} // namespace psdf
