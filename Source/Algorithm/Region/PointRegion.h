#pragma once

#include "../../Polygon/Point.h"
#include "LineRegion.h"
#include "PointRegionBoundVertex.h"
#include "Region.h"

namespace psdf
{

class PointRegion : public Region
{
  public:
    PointRegion(Point point, double cornerSign, size_t subdivisions, double initialBoundScale);
    PointRegion(std::vector<glm::dvec2> bounds, Point point, double cornerSign, size_t subdivisions);

    static void cutWithPoints(std::vector<PointRegion> &pointRegions, const std::vector<PointRegion> &cuttingRegions);
    static void cutWithLines(std::vector<PointRegion> &pointRegions, const std::vector<LineRegion> &lineRegions);

    void createMesh(std::vector<PointRegionBoundVertex> &vertices, std::vector<uint32_t> &indices,
                    Point fanCenter) const;

    Point getPoint() const;
    double getCornerSign() const;
    double getDistanceToPointInsideBounds(Point point) const override;

  private:
    Point mPoint;
    double mCornerSign;
    size_t mSubdivisions;
};

} // namespace psdf
