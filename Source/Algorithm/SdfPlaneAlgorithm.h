#pragma once

#include "../Polygon/Polygon.h"
#include "Region/LineRegion.h"
#include "Region/PointRegion.h"

namespace psdf
{

class SdfPlaneAlgorithm
{

  public:
    static void getResult(const Polygon::SharedPtr &pPolygon);

  private:
    SdfPlaneAlgorithm() = default;
};

} // namespace psdf
