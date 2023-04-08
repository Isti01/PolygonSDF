#pragma once

#include "../Algorithm/SdfPlaneAlgorithmOutput.h"
#include "Point.h"
#include "Segment.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Polygon : public std::enable_shared_from_this<Polygon>
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

    SdfPlaneAlgorithmOutput::SharedPtr getAlgorithmOutput() const;
    void runAlgorithm();

  private:
    Polygon(Points points, Segments segments);

    static Segments connectOrderedPoints(const std::vector<Point> &points);

  public:
    static Polygon::SharedPtr kExamplePolygon;

  private:
    SdfPlaneAlgorithmOutput::SharedPtr mpSdfPlaneAlgorithmOutput = nullptr;
    Points mPoints;
    Segments mSegments;
};

} // namespace psdf
