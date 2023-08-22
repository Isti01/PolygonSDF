#pragma once

#include "../../../Shape/Shape.h"
#include "../../RenderObject.h"
#include "./SdfAlgorithmOutputRenderer.h"

#include <Falcor.h>

namespace psdf
{
using namespace Falcor;

class SdfAlgorithmEdgeRegionRenderer : public SdfAlgorithmOutputRenderer
{
  public:
    using SharedPtr = std::shared_ptr<SdfAlgorithmEdgeRegionRenderer>;

    static SharedPtr create(GraphicsState::SharedPtr pModifiedDepthState, GraphicsState::SharedPtr pSimpleMeshState);

  protected:
    SdfAlgorithmEdgeRegionRenderer(GraphicsState::SharedPtr pModifiedDepthState,
                                   GraphicsState::SharedPtr pSimpleMeshState);

    void uploadShapeData() override;
};

} // namespace psdf
