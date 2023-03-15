#pragma once

#include "../../Polygon/Point.h"
#include "Region.h"

namespace psdf
{

class PointRegion : public Region
{
  public:
    PointRegion(Point point, float cornerSign);

  private:
    Point mPoint;
    float mCornerSign;
};

} // namespace psdf
