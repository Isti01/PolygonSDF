#pragma once

#include "Impl/SdfAlgorithmPointRegionRenderer.h"
#include "PolygonRenderer.h"

namespace psdf
{

class PolygonRendererFactory
{
  public:
    static PolygonRenderer::SharedPtr getPolygonRenderer();
    static PolygonRenderer::SharedPtr getAlgorithmOutputRenderer();

  private:
    PolygonRendererFactory() = default;
};

} // namespace psdf
