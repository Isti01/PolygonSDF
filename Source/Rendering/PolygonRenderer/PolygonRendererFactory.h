#pragma once

#include "PolygonRenderer.h"

namespace psdf
{

class PolygonRendererFactory
{
  public:
    static PolygonRenderer::SharedPtr getPolygonRenderer();

  private:
    PolygonRendererFactory() = default;
};

} // namespace psdf
