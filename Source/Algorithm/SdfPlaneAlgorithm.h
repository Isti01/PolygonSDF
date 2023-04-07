#pragma once

#include "../Polygon/Polygon.h"
#include "./SdfPlaneAlgorithmOutput.h"
#include "Region/LineRegion.h"
#include "Region/PointRegion.h"

namespace psdf
{

class SdfPlaneAlgorithm
{
  public:
    static SdfPlaneAlgorithmOutput calculateForPolygon(const Polygon::SharedPtr &pPolygon);

  private:
    SdfPlaneAlgorithm() = default;
};

} // namespace psdf
