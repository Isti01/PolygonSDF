#pragma once

#include "Impl/SdfAlgorithmVertexRegionRenderer.h"
#include "ShapeRenderer.h"

namespace psdf
{

class ShapeRendererFactory
{
  public:
    static ShapeRenderer::SharedPtr getEditorShapeRenderer();
    static ShapeRenderer::SharedPtr getAlgorithmOutputRenderer();

  private:
    ShapeRendererFactory() = default;
};

} // namespace psdf
