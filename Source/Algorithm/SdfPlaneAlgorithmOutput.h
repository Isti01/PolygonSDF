#pragma once

#include "Region/EdgeRegion.h"
#include "Region/VertexRegion.h"

#include <Falcor.h>

namespace psdf
{

class SdfPlaneAlgorithmOutput
{
  public:
    using SharedPtr = std::shared_ptr<SdfPlaneAlgorithmOutput>;
    static SharedPtr create(std::vector<VertexRegion> vertexRegions, std::vector<EdgeRegion> edgeRegions);

    std::vector<VertexRegion> getVertexRegions() const;
    std::vector<EdgeRegion> getEdgeRegions() const;

    bool saveJson(const std::string &path) const;

  protected:
    SdfPlaneAlgorithmOutput(std::vector<VertexRegion> vertexRegions, std::vector<EdgeRegion> edgeRegions);

  private:
    std::vector<VertexRegion> mVertexRegions;
    std::vector<EdgeRegion> mEdgeRegions;
};

} // namespace psdf
