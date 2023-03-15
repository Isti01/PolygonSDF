#pragma once

#include "../../Polygon/Segment.h"
#include "Region.h"

namespace psdf
{

class LineRegion : public Region
{
  public:
    LineRegion(const Segment &segment);

  private:
    Segment mSegment;
};

} // namespace psdf
