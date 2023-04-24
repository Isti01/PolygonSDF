#pragma once

#include "Region/LineRegion.h"
#include "Region/PointRegion.h"

#include <Falcor.h>

namespace psdf
{

class SdfPlaneAlgorithmOutput
{
  public:
    using SharedPtr = std::shared_ptr<SdfPlaneAlgorithmOutput>;
    static SharedPtr create(std::vector<PointRegion> pointRegions, std::vector<LineRegion> lineRegions);

    std::vector<PointRegion> getPointRegions() const;
    std::vector<LineRegion> getLineRegions() const;

    bool saveJson(const std::string &path) const;

  protected:
    SdfPlaneAlgorithmOutput(std::vector<PointRegion> pointRegions, std::vector<LineRegion> lineRegions);

  private:
    std::vector<PointRegion> mPointRegions;
    std::vector<LineRegion> mLineRegions;
};

} // namespace psdf
