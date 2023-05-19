#pragma once

#include <Falcor.h>

#include "../../../Polygon/Shape.h"
#include "../../RenderObject.h"
#include "./SdfAlgorithmOutputRenderer.h"

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmVertexRegionRenderer : public SdfAlgorithmOutputRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmVertexRegionRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pGraphicsState);

  protected:
    SdfAlgorithmVertexRegionRenderer(GraphicsState::SharedPtr pGraphicsState);

    void uploadShapeData() override;
};

} // namespace psdf
