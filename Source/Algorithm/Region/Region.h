#pragma once

#include "../../CommonConstants.h"
#include "../../Polygon/Point.h"
#include "./RegionBoundVertex.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Region
{
  public:
    void polyCut(const std::vector<Point> &points, const std::vector<glm::dvec2> &edgeVectors);

    Region();
    Region(std::vector<glm::dvec2> bounds);

    std::vector<glm::dvec2> getBounds() const;

    virtual double getDistanceToPointInsideBounds(Point point) const = 0;

    void createMesh(std::vector<RegionBoundVertex> &vertices, std::vector<uint32_t> &indices, Point fanCenter) const;

  private:
    std::vector<double> calculateVnd(glm::dvec2 edgeVector, double d);
    void calculateNewBounds(const std::vector<double> &vnd, std::vector<bool> &b);
    std::vector<int> getNeighborDifference(const std::vector<bool> &b);
    void applyNewBounds(std::vector<bool> &b, const std::vector<glm::dvec2> &w, size_t m0, size_t p1);

  protected:
    std::vector<glm::dvec2> mBounds;
};

} // namespace psdf
