#pragma once

#include "../Polygon/Polygon.h"
#include "./SdfPlaneAlgorithmOutput.h"
#include "Region/LineRegion.h"
#include "Region/PointRegion.h"
#include "SdfPlaneAlgorithmExecutionDesc.h"

namespace psdf
{

class SdfPlaneAlgorithm
{
  public:
    static SdfPlaneAlgorithmOutput::SharedPtr calculateForPolygon(const Polygon::SharedPtr &pPolygon,
                                                                  SdfPlaneAlgorithmExecutionDesc desc);

  private:
    SdfPlaneAlgorithm() = default;
};

} // namespace psdf
