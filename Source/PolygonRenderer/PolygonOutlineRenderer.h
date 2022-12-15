#pragma once

#include "../Polygon/Polygon.h"

namespace psdf
{

class PolygonOutlineRenderer
{
  public:
    virtual void setPolygon(const Polygon &polygon) = 0;
};

} // namespace psdf
