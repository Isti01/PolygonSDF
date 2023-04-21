#pragma once

#include "../../Polygon/Point.h"
#include "LineRegion.h"
#include "Region.h"

namespace psdf
{

class PointRegion : public Region
{
  public:
    static constexpr int32_t kSubDivs = 5;
    PointRegion(Point point, double cornerSign);
    PointRegion(std::vector<glm::dvec2> bounds, Point point, double cornerSign);

    static void cutWithPoints(std::vector<PointRegion> &pointRegions, const std::vector<PointRegion> &cuttingRegions);
    static void cutWithLines(std::vector<PointRegion> &pointRegions, const std::vector<LineRegion> &lineRegions);

    Point getPoint() const;
    double getCornerSign() const;
    double getDistanceToPointInsideBounds(Point point) const override;

  private:
    Point mPoint;
    double mCornerSign;
};

} // namespace psdf
