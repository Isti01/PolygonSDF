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
    LineRegion(std::vector<glm::dvec2> bounds, Segment segment);

    Segment getSegment() const;
    glm::dvec2 getDir() const;
    double getDistanceToPointInsideBounds(Point point) const override;

    static void cutWithPoints(std::vector<LineRegion> &lineRegions, const std::vector<PointRegion> &pointRegions);
    static void cutWithLines(std::vector<LineRegion> &lineRegions, const std::vector<LineRegion> &cuttingRegions);

  private:
    static glm::dvec2 computeParabolics(const glm::dvec2 &point, const glm::dvec2 &normal, const glm::dvec2 &bPoint);
    static glm::dvec2 computeBisectorIntersection(const glm::dvec2 &point, const glm::dvec2 &normal,
                                                  const glm::dvec2 &bPoint, const glm::dvec2 &bNormal,
                                                  const glm::dvec2 &g, bool isParallel);

  private:
    Segment mSegment;
};

} // namespace psdf
