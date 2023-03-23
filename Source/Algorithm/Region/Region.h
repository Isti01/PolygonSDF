#pragma once

#include "../../Polygon/Point.h"
#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class Region
{
  public:
    static constexpr float InitialBoundScale = 1e10f;

    void polyCut(const std::array<Point, 2> &points, const std::array<float2, 2> &edgeVectors);

  protected:
    Region();

  private:
    std::vector<float> calculateVnd(float2 edgeVector, float d);
    void calculateNewBounds(const std::vector<float> &vnd, std::vector<bool> &b);
    std::vector<int> getNeighborDifference(const std::vector<bool> &b);
    void applyNewBounds(std::vector<bool> &b, const std::vector<float2> &w, size_t m0, size_t p1);

  protected:
    std::vector<float2> mBounds;
};

} // namespace psdf
