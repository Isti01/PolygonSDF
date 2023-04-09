#pragma once

#include "Impl/SdfAlgorithmOutputRenderer.h"
#include "PolygonRenderer.h"

namespace psdf
{

class PolygonRendererFactory
{
  public:
    static PolygonRenderer::SharedPtr getPolygonRenderer();
    static SdfAlgorithmOutputRenderer::SharedPtr getAlgorithmOutputRenderer();

  private:
    PolygonRendererFactory() = default;
};

} // namespace psdf
