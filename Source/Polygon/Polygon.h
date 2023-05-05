#pragma once

#include "../Algorithm/SdfPlaneAlgorithmExecutionDesc.h"
#include "../Algorithm/SdfPlaneAlgorithmOutput.h"
#include "Point.h"
#include "Segment.h"
#include "SubPolygon.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Polygon : public std::enable_shared_from_this<Polygon>
{
  public:
    using Points = SubPolygon::Points;
    using Segments = SubPolygon::Segments;

    using FloatPoints = SubPolygon::FloatPoints;
    using FloatSegments = SubPolygon::FloatSegments;

    using SharedPtr = std::shared_ptr<Polygon>;
    static Polygon::SharedPtr kExamplePolygon;
    static Polygon::SharedPtr kSquarePolygon;

    static SharedPtr fromJson(const std::string &path);
    static SharedPtr create(std::vector<SubPolygon> polygons);

    bool saveJson(const std::string &path) const;

    Point getCenter() const;

    std::vector<SubPolygon> getPolygons() const;
    Segments getAllSegments() const;

    FloatSegments getAllFloatSegments() const;

    SdfPlaneAlgorithmOutput::SharedPtr getAlgorithmOutput() const;
    void runAlgorithm(SdfPlaneAlgorithmExecutionDesc desc = kDefaultSdfPlaneAlgorithmExecutionDesc);

  private:
    Polygon(std::vector<SubPolygon> polygons);

  private:
    SdfPlaneAlgorithmOutput::SharedPtr mpSdfPlaneAlgorithmOutput = nullptr;
    std::vector<SubPolygon> mPolygons;
};

} // namespace psdf
