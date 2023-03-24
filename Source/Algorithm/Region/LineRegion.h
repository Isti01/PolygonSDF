#pragma once

#include "../../Polygon/Segment.h"
#include "Region.h"

namespace psdf
{

class LineRegion : public Region
{
  public:
    LineRegion(const Segment &segment);
    LineRegion(std::vector<glm::dvec2> bounds, const Segment &segment);

    Segment getSegment() const;

  private:
    Segment mSegment;
};

} // namespace psdf
