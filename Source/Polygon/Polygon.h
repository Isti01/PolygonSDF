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
    using SharedPtr = std::shared_ptr<Polygon>;

    static SharedPtr create(const std::vector<Point> &points);

    Points getPoints() const;
    Segments getSegments() const;

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
