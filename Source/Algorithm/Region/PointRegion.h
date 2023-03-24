#pragma once

#include "../../Polygon/Point.h"
#include "Region.h"

namespace psdf
{

class PointRegion : public Region
{
  public:
    PointRegion(Point point, double cornerSign);
    PointRegion(std::vector<glm::dvec2> bounds, Point point, double cornerSign);

    static void cutWithPoints(std::vector<PointRegion> &pointRegions);

    Point getPoint() const;
    double getCornerSign() const;

  private:
    Point mPoint;
    double mCornerSign;
};

} // namespace psdf
