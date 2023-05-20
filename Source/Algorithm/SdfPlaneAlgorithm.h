#pragma once

#include "../Shape/Shape.h"
#include "./SdfPlaneAlgorithmOutput.h"
#include "Region/EdgeRegion.h"
#include "Region/VertexRegion.h"
#include "SdfPlaneAlgorithmExecutionDesc.h"

namespace psdf
{

class SdfPlaneAlgorithm
{
  public:
    static SdfPlaneAlgorithmOutput::SharedPtr calculateForShape(const Shape::SharedPtr &pShape,
                                                                SdfPlaneAlgorithmExecutionDesc desc);

  private:
    SdfPlaneAlgorithm() = default;
};

} // namespace psdf
