#pragma once

#include "../../../Polygon/Polygon.h"
#include "../../RenderObject.h"
#include "./SdfAlgorithmOutputRenderer.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmLineRegionRenderer : public SdfAlgorithmOutputRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmLineRegionRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);

  protected:
    SdfAlgorithmLineRegionRenderer(GraphicsState::SharedPtr pGraphicsState);

    void uploadPolygonData() override;
};

} // namespace psdf
