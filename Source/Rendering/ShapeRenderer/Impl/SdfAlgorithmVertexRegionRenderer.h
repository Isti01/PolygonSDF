#pragma once

#include <Falcor.h>

#include "../../../Shape/Shape.h"
#include "../../RenderObject.h"
#include "./SdfAlgorithmOutputRenderer.h"

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmVertexRegionRenderer : public SdfAlgorithmOutputRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmVertexRegionRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pModifiedDepthState, GraphicsState::SharedPtr pSimpleMeshState);

  protected:
    SdfAlgorithmVertexRegionRenderer(GraphicsState::SharedPtr pModifiedDepthState,
                                     GraphicsState::SharedPtr pSimpleMeshState);

    void uploadShapeData() override;
};

} // namespace psdf
