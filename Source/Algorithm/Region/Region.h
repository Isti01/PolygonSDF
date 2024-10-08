#pragma once

#include "../../Shape/Vertex.h"
#include "./EdgeRegionBoundVertex.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Region
{
  public:
    void polyCut(const std::vector<Vertex> &vertices, const std::vector<glm::dvec2> &edgeVectors);

    Region(double initialBoundScale);
    Region(std::vector<glm::dvec2> bounds);

    std::vector<glm::dvec2> getBounds() const;

    virtual double getDistanceToPointInsideBounds(Vertex point) const = 0;

    virtual ~Region() = default;

  private:
    void calculateVnd(std::vector<double> &vnd, glm::dvec2 edgeVector, double d);
    void calculateNewBounds(std::vector<int> &ind, const std::vector<double> &vnd, std::vector<bool> &b);
    void getNeighborDifference(std::vector<int> &ind, const std::vector<bool> &b);
    void applyNewBounds(std::vector<bool> &b, const std::vector<glm::dvec2> &w, size_t m0, size_t p1);

  protected:
    std::vector<glm::dvec2> mBounds;
};

} // namespace psdf
