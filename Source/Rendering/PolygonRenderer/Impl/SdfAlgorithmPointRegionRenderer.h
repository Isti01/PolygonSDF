#pragma once

#include <Falcor.h>

#include "../../../Polygon/Polygon.h"
#include "../../RenderObject.h"
#include "./SdfAlgorithmOutputRenderer.h"

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmPointRegionRenderer : public SdfAlgorithmOutputRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmPointRegionRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);

  protected:
    SdfAlgorithmPointRegionRenderer(GraphicsState::SharedPtr pGraphicsState);

    void uploadPolygonData() override;
};

} // namespace psdf
