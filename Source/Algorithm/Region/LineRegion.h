#pragma once

#include "../../Polygon/Segment.h"
#include "Region.h"

namespace psdf
{
class PointRegion;
class LineRegion : public Region
{
  public:
    LineRegion(const Segment &segment);
    LineRegion(std::vector<glm::dvec2> bounds, const Segment &segment);

    Segment getSegment() const;

    static void cutWithPoints(std::vector<LineRegion> &lineRegions, const std::vector<PointRegion> &pointRegions);

  private:
    Segment mSegment;
};

} // namespace psdf
