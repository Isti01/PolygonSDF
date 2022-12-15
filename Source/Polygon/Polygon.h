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
    using Points = std::shared_ptr<std::vector<Point>>;
    using Segments = std::shared_ptr<std::vector<Segment>>;
    using SharedPtr = std::shared_ptr<Polygon>;

    static SharedPtr create(const std::vector<Point> &points);

    Points getPoints() const;
    Segments getSegments() const;

  private:
    Polygon(Points points, Segments segments);

    static Segments connectOrderedPoints(const std::vector<Point> &points);

  private:
    Points mpPoints = nullptr;
    Segments mpSegments = nullptr;
};

} // namespace psdf
