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
    static SdfPlaneAlgorithmOutput::SharedPtr calculateForPolygon(const Polygon::SharedPtr &pPolygon,
                                                                  bool reorderPoints = true);

  private:
    SdfPlaneAlgorithm() = default;
};

} // namespace psdf
